/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** ACommands.hpp
*/

#ifndef ACOMMANDS_HPP_
# define ACOMMANDS_HPP_

#include "ICommands.hpp"

#include <map>
#include <vector>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

namespace server
{
    template<typename ArgList, typename Arg, typename Index>
    class ACommands : public ICommands<ArgList>
    {
        public:
            ACommands();
            virtual ~ACommands() = default;
        protected:
            virtual void signOn(ArgList &list) = 0;
            virtual void login(ArgList &list) = 0;
            virtual void logout(ArgList &list) = 0;
            virtual void addFriend(ArgList &list) = 0;
            virtual void acceptFriend(ArgList &list) = 0;
            virtual void callFriend(ArgList &list) = 0;
            virtual void acceptCall(ArgList &list) = 0;
            virtual void delFriend(ArgList &list) = 0;
        public:
            void call(Index &i, ArgList &list);
            std::vector<Arg> split(ArgList &list, const Arg &sep) const;
        protected:
            std::map<int, void(ACommands::*)(ArgList &)> _caller;
    };

    template<typename ArgList, typename Arg, typename Index>
    ACommands<ArgList, Arg, Index>::ACommands()
    {
        _caller[0] = &ACommands::signOn;
        _caller[1] = &ACommands::login;
        _caller[2] = &ACommands::logout;
        _caller[3] = &ACommands::addFriend;
        _caller[4] = &ACommands::acceptFriend;
        _caller[5] = &ACommands::callFriend;
        _caller[6] = &ACommands::acceptCall;
        _caller[7] = &ACommands::delFriend;
    }

    template<typename ArgList, typename Arg, typename Index>
    void ACommands<ArgList, Arg, Index>::call(Index &i, ArgList &list)
    {
        (this->*(_caller[i]))(list);
    }

    template<typename ArgList, typename Arg, typename Index>
    std::vector<Arg> ACommands<ArgList, Arg, Index>::split(ArgList &list, const Arg &sep) const
    {
        std::vector<Arg> args;
        boost::split(args, list, boost::is_any_of(sep), boost::token_compress_on);

        return args;
    }
}

#endif /* !ACOMMANDS_HPP_ */
