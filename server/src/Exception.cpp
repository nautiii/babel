/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Exception.cpp
*/

#include "Exception.hpp"

SQLiteException::SQLiteException(Flag flag) noexcept
    : _flag(flag)
{
    _msg[UNDEFINED] = "undefined error occured";
    _msg[OPEN]      = "database cannot be opened";
    _msg[CLOSE]     = "database cannot be closed";
    _msg[TABLE]     = "table(s) cannot be created";
    _msg[ONLINE]    = "user doesn't exist";
    _msg[EXIST]     = "unable to check user";
    _msg[INSERT]    = "insertion operation failed";
    _msg[LOG]       = "cannot change connection status";
    _msg[RELATION]  = "cannot add new relation";
    _msg[DELREL]    = "failed to delete relation";
    _msg[PASSWORD]  = "failed to retrieve password";
}

const char *SQLiteException::what() const noexcept
{
    return _msg[_flag].c_str();
}
