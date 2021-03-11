/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** ICommands.hpp
*/

#ifndef ICOMMANDS_HPP_
# define ICOMMANDS_HPP_

namespace server
{
    template<typename ArgList>
    class ICommands
    {
        public:
            virtual ~ICommands() = default;
        protected:
            virtual void signOn(ArgList &list) = 0;
            virtual void login(ArgList &list) = 0;
            virtual void logout(ArgList &list) = 0;
            virtual void addFriend(ArgList &list) = 0;
            virtual void acceptFriend(ArgList &list) = 0;
            virtual void callFriend(ArgList &list) = 0;
            virtual void acceptCall(ArgList &list) = 0;
            virtual void delFriend(ArgList &list) = 0;
    };
}

#endif /* !ICOMMANDS_HPP_ */
