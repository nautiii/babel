/*
** EPITECH PROJECT, 2020
** B-CPP-500-PAR-5-1-babel-thomas.raveneau
** File description:
** ANetworkManager
*/

#ifndef ANETWORKMANAGER_HPP_
#define ANETWORKMANAGER_HPP_

#include "INetworkManager.hpp"

namespace client {

    namespace networkManager {
        
        template <typename UIWindow, typename Socket, typename Package>
        class ANetworkManager : INetworkManager<Package> {
            public:
                ANetworkManager(string ip, int port, UIWindow *vwindow): _ip(ip), _port(port), _vwindow(vwindow) {};
                virtual ~ANetworkManager() {};

            protected:
                bool _isConnected = false;
                std::string _ip;
                int _port;
                Socket _socket;
                Package _pkg;
                UIWindow *_vwindow;
        };
    }

}

#endif /* !ANETWORKMANAGER_HPP_ */
