/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** ClientInfos.hpp
*/

#ifndef CLIENTINFOS_HPP_
# define CLIENTINFOS_HPP_

#include <string>

namespace server
{
    struct ClientInfos
    {
        std::string pseudo;
        bool connected;
        bool deconnect;

        explicit ClientInfos(const std::string &psd, bool co=false, bool deco=false) : pseudo(psd), connected(co), deconnect(deco) {}
    };
}

#endif /* !CLIENTINFOS_HPP_ */