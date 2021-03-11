/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** IHandler.hpp
*/

#ifndef IHANDLER_HPP_
# define IHANDLER_HPP_

#include "INetwork.hpp"

namespace server
{
    template<class Response>
    class IHandler
    {
        public:
            virtual ~IHandler() = default;
        protected:
            virtual void run() = 0;
            virtual void read() = 0;
            virtual void write(const Response &pkg) = 0;
    };
}

#endif /* !IHANDLER_HPP_ */
