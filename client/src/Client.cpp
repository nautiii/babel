/*
** EPITECH PROJECT, 2020
** B-CPP-500-PAR-5-1-babel-thomas.raveneau
** File description:
** Client
*/

#include "Client.hpp"

using namespace std;
using namespace client;

Client::Client(string ip, int port, int ac, char **av)
{
    _vwindow  = new QtUserInterface(ac, av);
    _networkManager = new QtNetwork(ip, port, std::move(_vwindow));
}

Client::~Client()
{
}

void Client::run()
{
    _networkManager->connectSocket();
    _vwindow->setNetworkManager(_networkManager);
}
