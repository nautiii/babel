/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** IServer.hpp
*/

#ifndef ISERVER_HPP_
# define ISERVER_HPP_

namespace server
{
    template<typename Socket>
    class IServer
    {
        public:
            virtual ~IServer() = default;
        protected:
            virtual void run() = 0;
            virtual void handleClient(Socket socket) = 0;
            virtual void waitEvent() = 0;
    };
}

#endif /* !ISERVER_HPP_ */
