/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Commands.hpp
*/

#ifndef COMMANDS_HPP_
# define COMMANDS_HPP_

#include "ACommands.hpp"
#include "Protocol.hpp"

#include <string>
#include <cctype>
#include <vector>

using namespace std;
using namespace protocol;

namespace server
{
    namespace asio
    {
        class Commands : public ACommands<string, string, Request>
        {
            public:
                Commands() = default;
                ~Commands() = default;
            protected:
                virtual void signOn(string &list) = 0;
                virtual void login(string &list) = 0;
                virtual void logout(string &list) = 0;
                virtual void addFriend(string &list) = 0;
                virtual void acceptFriend(string &list) = 0;
                virtual void callFriend(string &list) = 0;
                virtual void acceptCall(string &list) = 0;
                virtual void delFriend(string &list) = 0;
            protected:
                bool isAlphaNum(const string &s) const;
                bool missingArgs(const size_t &size, const vector<string> &args) const;
        };
    }
}

using namespace server::asio;

#endif /* !COMMANDS_HPP_ */
