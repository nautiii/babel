/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Receiver.hpp
*/

#ifndef RECEIVER_HPP_
# define RECEIVER_HPP_

#include "AReceiver.hpp"
#include "Protocol.hpp"

#include <iostream>
#include <array>
#include <bitset>
#include <string>

# define DEFAULT_SIZE 512
# define nullpkg      { 0, 0, 0, static_cast<protocol::Request>(0), "" }

using namespace std;
using namespace protocol;

namespace server
{
    namespace asio
    {
        typedef Package<Request, string> ClientPackage;

        class Receiver : public AReceiver<char *, size_t, ClientPackage>
        {
            public:
                Receiver(const size_t size=DEFAULT_SIZE);
                ~Receiver();
            public:
                ClientPackage deserialize() final;
            private:
                void clear() noexcept;
            private:
                bool   _uncomplete;
                size_t _len;
                ClientPackage _pkg;
        };
    }
}

using namespace server::asio;

#endif /* !RECEIVER_HPP_ */