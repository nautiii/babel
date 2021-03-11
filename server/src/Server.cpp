/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Server.cpp
*/

#include "Server.hpp"

AsioServer::AsioServer(const char **av)
    : _context(1), _signals(_context, SIGINT, SIGTERM), _acceptor(_context, tcp::endpoint(tcp::v4(), (av[1]) ? atoi(av[1]) : DEFAULT_PORT)), _stop(false)
{
    cout << "server launched on - " << _acceptor.local_endpoint() << endl;
}

void AsioServer::run()
{
    waitEndSignal();
    loop();
    _context.stop();
}

void AsioServer::loop()
{
    while (!_stop) {
        waitEvent();
        accept();
        deconnect();
        updClient();
        this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

void AsioServer::waitEndSignal()
{
    _signals.async_wait(
        [&](auto, auto) {
            cout << "server shutdown" << endl;
            _stop = true;
        }
    );
}

void AsioServer::waitEvent()
{
    if (_context.stopped())
        _context.restart();
    _context.run_one();
}

void AsioServer::accept()
{
    _acceptor.async_accept(
        [this](boost::system::error_code e, tcp::socket socket)
        {
            if (!e)
                return handleClient(move(socket));
            cout << e << endl;
        }
    );
}

void AsioServer::deconnect()
{
    for (deque<unique_ptr<Handler>>::iterator it = _clients.begin(); it != _clients.end(); ) {
        if((*it)->getInfos().deconnect)
            it = _clients.erase(it);
        else
            ++it;
    }
}

void AsioServer::handleClient(tcp::socket socket)
{
    auto client = make_unique<Handler>(_acceptor.local_endpoint().port(), move(socket));

    _clients.push_back(move(client));
    _clients.back()->run();
}

void AsioServer::updClient()
{
    vector<MinimalHandler> list;

    for (const auto &client : _clients)
        list.push_back(make_tuple(client->getInfos().pseudo, &client->getSocket()));
    for (auto &client : _clients)
        client->setUserList(list);
}
