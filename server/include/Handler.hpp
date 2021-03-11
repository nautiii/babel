/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Handler.hpp
*/

#ifndef HANDLER_HPP_
# define HANDLER_HPP_

#include "AsioPkg.hpp"
#include "AHandler.hpp"
#include "Commands.hpp"
#include "Storage.hpp"
#include "Receiver.hpp"
#include "ClientInfos.hpp"

#include <bitset>
#include <tuple>
#include <chrono>

#include <boost/asio.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

using namespace boost::asio;
using namespace boost::serialization;
using namespace boost::archive;
using namespace protocol::asio;

using ip::tcp;

namespace server
{
    namespace asio
    {
        typedef tuple<string, tcp::socket *> MinimalHandler;

        class Handler : public AHandler<AsioPackage, SQLite, tcp::socket>, public Commands
        {
            public:
                Handler(int port, tcp::socket socket);
                ~Handler() = default;
            public:
                void run() final;
            public:
                const ClientInfos &getInfos() const noexcept;
                void setUserList(const vector<tuple<string, tcp::socket *>> &list) noexcept;
            private:
                void read() final;
                void write(const AsioPackage &pkg) final;
                void write(tcp::socket *socket, const AsioPackage &pkg);
            private:
                void interpret(size_t &length);
                void send(Response r, const string &args={});
                void send(tcp::socket *socket, Response r, const string &args={});
                const AsioPackage make_pkg(Response r, const string &args) const noexcept;
                const string respMsg(const vector<string> &args={}, bool err=true) const noexcept;
                bool validPkg(const ClientPackage &pkg) const noexcept;
            private:
                void signOn(string &list) final;
                void login(string &list) final;
                void logout(string &list) final;
                void addFriend(string &list) final;
                void acceptFriend(string &list) final;
                void callFriend(string &list) final;
                void acceptCall(string &list) final;
                void delFriend(string &list) final;
            private:
                int         _port;
                ClientInfos _infos;
                Receiver    _rcv;
                vector<MinimalHandler> _list;
        };
    }
}

#endif /* !HANDLER_HPP_ */
