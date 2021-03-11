/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** AServer.hpp
*/

#ifndef ASERVER_HPP_
# define ASERVER_HPP_

#include "IServer.hpp"

#include <deque>
#include <memory>

namespace server
{
    template<typename Socket, typename Client>
    class AServer : public IServer<Socket>
    {
        public:
            ~AServer() = default;
        protected:
            virtual void run() = 0;
            virtual void handleClient(Socket socket) = 0;
            virtual void waitEvent() = 0;
        protected:
            std::deque<std::unique_ptr<Client>> _clients;
    };
}

#endif /* !ASERVER_HPP_ */
