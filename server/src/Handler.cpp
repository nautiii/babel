/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Handler.cpp
*/

#include "Handler.hpp"

Handler::Handler(int port, tcp::socket socket)
    : AHandler(move(socket)), _port(port), _infos("")
{
    cout << "client connected on - " << _socket.local_endpoint() << endl;
}

void Handler::run()
{
    read();
}

const server::ClientInfos &Handler::getInfos() const noexcept
{
    return _infos;
}

void Handler::setUserList(const vector<tuple<string, tcp::socket *>> &list) noexcept
{
    _list.clear();
    _list = list;
}

void Handler::read()
{
    _socket.async_read_some(
        boost::asio::buffer(_rcv.getData(), _rcv.getSize()),
        [this](boost::system::error_code e, size_t length)
        {
            if (e) {
                cerr << e << endl;
                _infos.deconnect = true;
                _db.connect(_infos.pseudo, false);
            } else {
                interpret(length);
                read();
            }
        }
    );
}

void Handler::write(const AsioPackage &pkg)
{
    stringstream ss(ios_base::binary | ios_base::out | ios_base::in);
    binary_oarchive oa(ss, no_header);
    oa << pkg;

    const_buffer buffer(boost::asio::buffer(ss.str()));

    _socket.async_write_some(buffer,
        [this](boost::system::error_code e, size_t length)
        {
            if (!e)
                cout << length << " bits sent" << endl;
            else
                cout << "error << " << e.value() << ": " << e.message() << endl;
        }
    );
}

void Handler::write(tcp::socket *socket, const AsioPackage &pkg)
{
    stringstream ss(ios_base::binary | ios_base::out | ios_base::in);
    binary_oarchive oa(ss, no_header);
    oa << pkg;

    const_buffer buffer(boost::asio::buffer(ss.str()));

    socket->async_write_some(buffer,
        [this](boost::system::error_code e, size_t length)
        {
            if (!e)
                cout << length << " bits sent" << endl;
            else
                cout << "error << " << e.value() << ": " << e.message() << endl;
        }
    );
}

void Handler::interpret(size_t &length)
{
    ClientPackage pkg = _rcv.deserialize();

    cout << length << " bits red" << endl;
    if (!validPkg(pkg))
        return ;
    if (!_infos.connected && (pkg.cmd ^ Request::REGISTER && pkg.cmd ^ Request::LOGIN))
        send(Response::NOT_CONNECTED, respMsg({ "must be connected" }));
    else if (pkg.cmd < 0 || pkg.cmd >= Request::TOTAL)
        send(Response::INVALID_CMD, respMsg({ to_string(pkg.cmd) }));
    try {
        call(pkg.cmd, pkg.args);    
    } catch (SQLiteException &e) {
        cout << e.what() << endl;
    }
}

void Handler::send(Response r, const string &args)
{
    const auto pkg = make_pkg(r, args);

    write(pkg);
}

void Handler::send(tcp::socket *socket, Response r, const string &args)
{
    const auto pkg = make_pkg(r, args);

    if (socket)
        write(socket, pkg);
}

const AsioPackage Handler::make_pkg(Response r, const string &args) const noexcept
{ 
    return AsioPackage {
        MAGIC,
        _port,
        _socket.local_endpoint().port(),
        r,
        args
    };
}

const string Handler::respMsg(const vector<string> &args, bool err) const noexcept
{
    string msg((err) ? "err" : "ok");

    for (const auto i : args)
        msg += SEPARATOR + i;
    return msg;
}

bool Handler::validPkg(const ClientPackage &pkg) const noexcept
{
    return (pkg.magic == MAGIC && pkg.snder == _socket.local_endpoint().port() && pkg.rcver == _port);
}

void Handler::signOn(string &list)
{
    auto args = split(list, SEPARATOR);

    if (missingArgs(2, args))
        return send(Response::REGISTER_ERR, respMsg({ "missing argument" }));
    if (!isAlphaNum(args[0]) || !isAlphaNum(args[1]))
        return send(Response::REGISTER_ERR, respMsg({ "non alphanumeric username/password" }));
    if (_db.exist(args[0]))
        return send(Response::REGISTER_ERR, respMsg({ "user already exists" }));
    _db.addClient(args[0], args[1]);
    send(Response::REGISTER_OK, respMsg({ "successfuly registered" }, false));
    _infos.pseudo = args[0];
    _infos.connected = true;
}

void Handler::login(string &list)
{
    auto args = split(list, SEPARATOR);

    if (missingArgs(2, args))
        return send(Response::LOGIN_ERR, respMsg({ "missing argument" }));
    if (!isAlphaNum(args[0]) || !isAlphaNum(args[1]))
        return send(Response::LOGIN_ERR, respMsg({ "non alphanumeric username/password" }));
    if (!_db.exist(args[0]))
        return send(Response::LOGIN_ERR, respMsg({ "user doesn't exist" }));
    if (_db.isOnline(args[0]))
        return send(Response::LOGIN_ERR, respMsg({ "user already connected" }));
    if (_db.getPassword(args[0]) != args[1])
        return send(Response::LOGIN_ERR, respMsg({ "wrong password" }));
    _db.connect(args[0]);
    send(Response::LOGIN_OK, respMsg(_db.getRelations(args[0]), false));
    _infos.pseudo = args[0];
    _infos.connected = true;
}

void Handler::logout(string &list)
{
    auto args = split(list, SEPARATOR);

    if (missingArgs(1, args))
        return send(Response::LOGOUT_ERR, respMsg({ "missing argument" }));
    if (!isAlphaNum(args[0]))
        return send(Response::LOGOUT_ERR, respMsg({ "non alphanumeric username" }));
    if (!_db.exist(args[0]))
        return send(Response::LOGOUT_ERR, respMsg({ "user doesn't exist" }));
    _db.connect(args[0], false);
    send(Response::LOGOUT_OK, respMsg({ "successfuly logout" }, false));
    _infos.connected = false;
}

void Handler::addFriend(string &list)
{
    auto args = split(list, SEPARATOR);

    if (missingArgs(1, args))
        return send(Response::ADDFRIEND_ERR, respMsg({ "missing argument" }));
    if (!isAlphaNum(args[0]))
        return send(Response::ADDFRIEND_ERR, respMsg({ "non alphanumeric username" }));
    if (!_db.exist(args[0]))
        return send(Response::ADDFRIEND_ERR, respMsg({ "user doesn't exist" }));
    if (_infos.pseudo == args[0])
        return send(Response::ADDFRIEND_ERR, respMsg({ "eat a curly" }));
    auto friends = _db.getRelations(_infos.pseudo);
    if (find(friends.begin(), friends.end(), args[0]) != friends.end())
        return send(Response::ADDFRIEND_ERR, respMsg({ "this user is already your friend" }));
    auto socket = get<1>(_list[distance(_list.begin(), find_if(_list.begin(), _list.end(),
        [args](const tuple<string, tcp::socket *> &node) {
            return get<0>(node) == args[0];
        }
    ))]);
    send(socket, Response::ACCEPT_FRIEND, respMsg({ _infos.pseudo }, false));
    send(Response::ADDFRIEND_OK, respMsg({ "request successfuly sent" }, false));
}

void Handler::acceptFriend(string &list)
{
    auto args = split(list, SEPARATOR);

    if (missingArgs(2, args))
        return send(Response::ACCEPT_FRIEND_ERR, respMsg({ "missing argument" }));
    if (!isAlphaNum(args[0]) || (args[1] != "yes" && args[1] != "no"))
        return send(Response::ACCEPT_FRIEND_ERR, respMsg({ "wrong argument sent" }));
    if (!_db.exist(args[0]))
        return send(Response::ACCEPT_FRIEND_ERR, respMsg({ "user doesn't exist" }));
    if (args[1] == "yes") {
        _db.addRelation(args[0], _infos.pseudo);
        auto socket = get<1>(_list[distance(_list.begin(), find_if(_list.begin(), _list.end(),
            [args](const tuple<string, tcp::socket *> &node) {
                return get<0>(node) == args[0];
            }
        ))]);
        send(socket, Response::ACCEPTED_FRIEND, respMsg({ _infos.pseudo }, false));
    }
    send(Response::ACCEPT_FRIEND_OK, respMsg({ "successfuly handle relation" }, false));
}

void Handler::delFriend(string &list)
{
    auto args = split(list, SEPARATOR);

    if (missingArgs(1, args))
        return send(Response::DELETE_ERR, respMsg({ "missing argument" }));
    if (!isAlphaNum(args[0]))
        return send(Response::DELETE_ERR, respMsg({ "wrong argument sent" }));
    if (!_db.exist(args[0]))
        return send(Response::DELETE_ERR, respMsg({ "user doesn't exist" }));
    auto friends = _db.getRelations(_infos.pseudo);
    if (find(friends.begin(), friends.end(), args[0]) == friends.end())
        return send(Response::ADDFRIEND_ERR, respMsg({ "this user isn't your friend" }));
    _db.delRelation(args[0], _infos.pseudo);
    send(Response::DELETE_OK, respMsg({ "successfuly delete relation" }, false));
}

void Handler::callFriend(string &list)
{
    auto args = split(list, SEPARATOR);

    if (missingArgs(2, args))
        return send(Response::CALL_ERR, respMsg({ "missing argument" }));
    if (!isAlphaNum(args[0]))
        return send(Response::CALL_ERR, respMsg({ "non alphanumeric username" }));
    if (!_db.exist(args[0]) || stoi(args[1]) == 0)
        return send(Response::CALL_ERR, respMsg({ "wrong argument sent" }));
    auto socket = get<1>(_list[distance(_list.begin(), find_if(_list.begin(), _list.end(),
        [args](const tuple<string, tcp::socket *> &node) {
            return get<0>(node) == args[0];
        }
    ))]);
    send(socket, Response::ACCEPT_CALL, respMsg({ _infos.pseudo, _socket.local_endpoint().address().to_string(), args[1] }, false));
    cout << _infos.pseudo << " " << _socket.local_endpoint().address().to_string() << " " << args[1] << " " << endl;
    send(Response::CALL_OK, respMsg({ "request successfuly sent" }, false));
}

void Handler::acceptCall(string &list)
{
    auto args = split(list, SEPARATOR);

    if (missingArgs(2, args))
        return send(Response::ACCEPT_CALL_ERR, respMsg({ "missing argument" }));
    if (!isAlphaNum(args[0]) || (args[1] != "yes" && args[1] != "no"))
        return send(Response::ACCEPT_CALL_ERR, respMsg({ "wrong argument sent" }));
    if (!_db.exist(args[0]))
        return send(Response::ACCEPT_CALL_ERR, respMsg({ "user doesn't exist" }));
    if (args[1] == "yes") {
        auto socket = get<1>(_list[distance(_list.begin(), find_if(_list.begin(), _list.end(),
            [args](const tuple<string, tcp::socket *> &node) {
                return get<0>(node) == args[0];
            }
        ))]);
        send(socket, Response::ACCEPTED_CALL, respMsg({ _infos.pseudo }, false));
    }
    send(Response::ACCEPT_CALL_OK, respMsg({ "successfuly handle call" }, false));
}
