/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Exception.hpp
*/

#ifndef EXCEPTION_HPP_
# define EXCEPTION_HPP_

#include <array>
#include <exception>
#include <iostream>

namespace server
{
    namespace exception
    {
        class SQLiteException : public std::exception
        {
            public:
                enum Flag { UNDEFINED, OPEN, CLOSE, TABLE, ONLINE, EXIST, INSERT, LOG, RELATION, DELREL, PASSWORD, TOTAL };
            public:
                SQLiteException(Flag flag) noexcept;
                virtual ~SQLiteException() noexcept = default;

                virtual const char *what() const noexcept;
            private:
                Flag _flag;
                std::array<std::string, TOTAL> _msg;
        };
    }
}

using namespace server::exception;

#endif /* !EXCEPTION_HPP_ */
