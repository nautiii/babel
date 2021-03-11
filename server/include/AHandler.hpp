/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** AHandler.hpp
*/

#ifndef AHANDLER_HPP_
# define AHANDLER_HPP_

#include "IHandler.hpp"
#include <utility>

namespace server
{
    template<class Response, class Database, typename Socket>
    class AHandler : public IHandler<Response>
    {
        public:
            AHandler(Socket socket) noexcept;
            virtual ~AHandler() = default;
        public:
            virtual void run() = 0;
            virtual Socket &getSocket() noexcept;
        protected:
            virtual void read() = 0;
            virtual void write(const Response &pkg) = 0;
        protected:
            Database _db;
            Socket   _socket;
    };

    template<class Response, class Database, typename Socket>
    AHandler<Response, Database, Socket>::AHandler(Socket socket) noexcept
        : _socket(std::move(socket))
    {

    }

    template<class Response, class Database, typename Socket>
    Socket &AHandler<Response, Database, Socket>::getSocket() noexcept
    {
        return _socket;
    }
}

#endif /* !AHANDLER_HPP_ */
