/*
** EPITECH PROJECT, 2020
** B-CPP-500-PAR-5-1-babel-thomas.raveneau
** File description:
** QtUserInterface
*/

#include "QtUserInterface.hpp"
#include "connectionPage.hpp"
#include "mainPage.hpp"
#include <QtWidgets/QPushButton>
#include <iostream>

QtUserInterface::QtUserInterface(int ac, char **av)
{
    WidgetList = new QListWidget;
    PageList = new QStackedWidget();
    PageList->insertWidget(1, new MainPage(this, WidgetList));
    PageList->insertWidget(0, new ConnectionPage(this, WidgetList));
    PageList->setCurrentWidget(PageList->widget(0));
    PageList->show();
}

QtUserInterface::~QtUserInterface()
{
}

void QtUserInterface::changeState(page_state_t newState) 
{
    PageList->setCurrentWidget(PageList->widget(newState));
}

void QtUserInterface::setNetworkManager(QtNetwork *networkManager)
{
    _networkManager = networkManager;
}

QtNetwork *QtUserInterface::getNetworkManager() 
{
    return (_networkManager);
}

QTcpSocket *QtUserInterface::getVOIPsocket()
{
    return VOIP_socket;
}

void QtUserInterface::setVOIPsocket(QTcpSocket *newSocket)
{
    VOIP_socket = newSocket;
}


void QtUserInterface::receiveDataPacket(DataPacket packet)
{
    protocol::Response cmdResponse = packet.extractResponse();
    totalPayload = packet.extractData();

    cout << "---------" << endl;
    for (auto i : totalPayload) {
        cout << i << endl;
    }
    cout << "=========" << endl;

    if (totalPayload.size() >= 2) {
        currentPayload = totalPayload[1];
    }

    switch (cmdResponse)
    {
        case(protocol::Response::NOT_CONNECTED):
            //trigger not connected()
            return;
        case(protocol::Response::INVALID_CMD):
            //trigger error request()
            return;
        case(protocol::Response::REGISTER_ERR):
            QMetaObject::invokeMethod(PageList->widget(0), "OnFailedReg", Qt::QueuedConnection);
            return;
        case(protocol::Response::REGISTER_OK):
            QMetaObject::invokeMethod(PageList->widget(0), "OnSuccessReg", Qt::QueuedConnection);
            return;
        case(protocol::Response::LOGIN_ERR):
            QMetaObject::invokeMethod(PageList->widget(0), "OnFailedLog", Qt::QueuedConnection);
            return;
        case(protocol::Response::LOGIN_OK):
            QMetaObject::invokeMethod(PageList->widget(0), "OnSuccessLog", Qt::QueuedConnection);
            return;
        case(protocol::Response::LOGOUT_ERR):
            QMetaObject::invokeMethod(PageList->widget(1), "OnSuccessLogOutRequest", Qt::QueuedConnection);
            return;
        case(protocol::Response::LOGOUT_OK):
            QMetaObject::invokeMethod(PageList->widget(1), "OnFailedLogOutRequest", Qt::QueuedConnection);
            return;
        case(protocol::Response::ADDFRIEND_OK):
            QMetaObject::invokeMethod(PageList->widget(1), "OnSuccessFriendRequest", Qt::QueuedConnection);
            return;
        case(protocol::Response::ADDFRIEND_ERR):
            QMetaObject::invokeMethod(PageList->widget(1), "OnFailedFriendRequest", Qt::QueuedConnection);
            return;
        case(protocol::Response::ACCEPT_FRIEND):
            QMetaObject::invokeMethod(PageList->widget(1), "OnReceiveFriendRequest", Qt::QueuedConnection);
            return;
        case(protocol::Response::ACCEPTED_FRIEND):
            QMetaObject::invokeMethod(PageList->widget(1), "OnFriendAcceptedRequest", Qt::QueuedConnection);
            return;
        case(protocol::Response::ACCEPT_FRIEND_OK):
            QMetaObject::invokeMethod(PageList->widget(1), "OnSuccessAcceptFriendRequest", Qt::QueuedConnection);
            return;
        case(protocol::Response::ACCEPT_FRIEND_ERR):
            QMetaObject::invokeMethod(PageList->widget(1), "OnFailedAcceptFriendRequest", Qt::QueuedConnection);
            return;
        case(protocol::Response::CALL_OK):
            QMetaObject::invokeMethod(PageList->widget(1), "OnSuccessCallRequest", Qt::QueuedConnection);
            return;
        case(protocol::Response::CALL_ERR):
            QMetaObject::invokeMethod(PageList->widget(1), "OnFailedCallRequest", Qt::QueuedConnection);
            return;
        case(protocol::Response::ACCEPT_CALL):
            QMetaObject::invokeMethod(PageList->widget(1), "OnCallAcceptRequest", Qt::QueuedConnection);
            return;
        case(protocol::Response::ACCEPTED_CALL):
            QMetaObject::invokeMethod(PageList->widget(1), "OnCallAcceptedRequest", Qt::QueuedConnection);
            return;
        case(protocol::Response::ACCEPT_CALL_OK):
            QMetaObject::invokeMethod(PageList->widget(1), "OnSuccessCallAcceptRequest", Qt::QueuedConnection);
            return;
        case(protocol::Response::ACCEPT_CALL_ERR):
            QMetaObject::invokeMethod(PageList->widget(1), "OnFailedCallAcceptRequest", Qt::QueuedConnection);
            return;
        case(protocol::Response::DELETE_OK):
            QMetaObject::invokeMethod(PageList->widget(1), "OnSuccessDeleteRequest", Qt::QueuedConnection);
            return;
        case(protocol::Response::DELETE_ERR):
            QMetaObject::invokeMethod(PageList->widget(1), "OnFailedDeleteRequest", Qt::QueuedConnection);
            return;
        
    }
    return;
}

std::string QtUserInterface::getcurrentPayload()
{
    return currentPayload;
}

std::vector<std::string> QtUserInterface::getTotalPayload()
{
    return totalPayload;
}

QStackedWidget* QtUserInterface::getPageList()
{
    return PageList;
}

QListWidget* QtUserInterface::getList()
{
    return WidgetList;
}

void QtUserInterface::login()
{
    changeState(page_state_t::connection_page);
}

void QtUserInterface::logout()
{
    QApplication::quit();
}
