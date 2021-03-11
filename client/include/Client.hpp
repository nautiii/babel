/*
** EPITECH PROJECT, 2020
** B-CPP-500-PAR-5-1-babel-thomas.raveneau
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include "QtNetwork.hpp"
#include "QtUserInterface.hpp"
#include <QApplication>

using namespace client::networkManager::qt;

namespace client {

    class Client {
        public:
            Client(string ip, int port, int ac, char **av);
            ~Client();

            void run();

        protected:
            QtNetwork *_networkManager;
            QtUserInterface *_vwindow;
    };

}

#endif /* !CLIENT_HPP_ */
