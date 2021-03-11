/*
** EPITECH PROJECT, 2020
** B-CPP-500-PAR-5-1-babel-thomas.raveneau
** File description:
** QtUserInterface
*/

#ifndef QTUSERINTERFACE_HPP_
#define QTUSERINTERFACE_HPP_


#include <QObject>
#include <QtWidgets/QtWidgets>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QApplication>
#include <memory>
#include "QtNetwork.hpp"
#include "DataPacket.hpp"
#include "IUserInterface.hpp"


using namespace client::networkManager::qt;

class QtUserInterface: public QObject, public IUserInterface {    
    public:
        QtUserInterface(int ac, char **av);
        ~QtUserInterface();
        
        void changeState(page_state_t newState);
        void login();
        void logout();

        QStackedWidget *getPageList();
        QListWidget *getList();
        QTcpSocket *getVOIPsocket();
        void setVOIPsocket(QTcpSocket *);

        void setNetworkManager(QtNetwork *networkManager);
        QtNetwork *getNetworkManager();
        void receiveDataPacket(DataPacket packet);
        std::string getcurrentPayload();
        std::vector<std::string> getTotalPayload();

    private:
        std::vector<std::string> totalPayload;
        std::string currentPayload;
        QStackedWidget *PageList;
        QListWidget *WidgetList;
        QtNetwork *_networkManager;
        QTcpSocket *VOIP_socket;
};

#endif /* !QTUSERINTERFACE_HPP_ */
