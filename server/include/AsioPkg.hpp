/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** AsioPkg.hpp
*/

#ifndef ASIOPACKAGE_HPP_
# define ASIOPACKAGE_HPP_

#include "Protocol.hpp"

#include <string>

#include <boost/serialization/binary_object.hpp>
#include <boost/serialization/serialization.hpp>

namespace protocol
{
    namespace asio
    {
        struct AsioPackage : public Package<Response, std::string>
        {
            template<typename Archive>
            void serialize(Archive &ar, const unsigned int)
            {
                ar & magic;
                ar & snder;
                ar & rcver;
                ar & cmd;
                ar & args;
            }

            void reset()
            {
                magic = 0;
                snder = 0;
                rcver = 0;
                args.clear();
            }
        };
    }
}

#endif /* !ASIOPACKAGE_HPP_ */
