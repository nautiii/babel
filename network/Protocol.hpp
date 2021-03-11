/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Protocol.hpp
*/

#ifndef PROTOCOL_HPP_
# define PROTOCOL_HPP_

# define MAGIC     0xC0FFEE // 12648430
# define SEPARATOR ":"

namespace protocol
{
    enum Request {
        REGISTER,
        LOGIN,
        LOGOUT,
        FRIEND,
        FACCEPT,
        CALL,
        CACCEPT,
        DELETE,
        TOTAL,
    };

    enum Response {
        NOT_CONNECTED,
        INVALID_CMD,
        REGISTER_ERR,
        REGISTER_OK,
        LOGIN_ERR,
        LOGIN_OK,
        LOGOUT_ERR,
        LOGOUT_OK,
        ADDFRIEND_OK,
        ADDFRIEND_ERR,
        ACCEPT_FRIEND,
        ACCEPTED_FRIEND,
        ACCEPT_FRIEND_OK,
        ACCEPT_FRIEND_ERR,
        CALL_OK,
        CALL_ERR,
        ACCEPT_CALL,
        ACCEPTED_CALL,
        ACCEPT_CALL_OK,
        ACCEPT_CALL_ERR,
        DELETE_OK,
        DELETE_ERR,
    };

    template<typename Code, typename Args>
    struct Package
    {
        int magic;
        int snder;
        int rcver;

        Code cmd;
        Args args;
    };
}

#endif /* !PROTOCOL_HPP_ */
