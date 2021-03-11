/*
** EPITECH PROJECT, 2020
** B-CPP-500-PAR-5-1-babel-thomas.raveneau
** File description:
** INetworkManager
*/

#ifndef INETWORKMANAGER_HPP_
#define INETWORKMANAGER_HPP_

#include "Protocol.hpp"

#include <memory>
#include <vector>
#include <iostream>

using namespace protocol;
using namespace std;

namespace client {

    namespace networkManager {

        template <typename Package>
        class INetworkManager {
            public:
                virtual ~INetworkManager() = default;

                virtual void connectSocket() = 0;
                virtual void disconnectSocket() = 0;

                virtual const Package makePackage(Request req, string args) const noexcept = 0;

                virtual void send(Request req, string args) = 0;
                // virtual void receive() = 0;

            protected:
            private:
        };

    }

}

#endif /* !INETWORKMANAGER_HPP_ */
