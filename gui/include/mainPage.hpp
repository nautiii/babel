/*
** EPITECH PROJECT, 2020
** B-CPP-500-PAR-5-1-babel-thomas.raveneau
** File description:
** mainPage
*/

#ifndef MAINPAGE_HPP_
#define MAINPAGE_HPP_


#include <QObject>
#include "QtUserInterface.hpp"
#include <QtWidgets/QPushButton>
#include <QtWidgets/QtWidgets>
#include "QtUdpNetwork.hpp"
#include "PortAudio.hpp"

class MainPage : public QWidget {
    Q_OBJECT
    public:
        MainPage(QtUserInterface *window, QListWidget *WidgetList);
        ~MainPage();
    protected:
    private slots:
        void pushButtonAddFriend();
        void pushButtonDeleteFriend();
        void pushButtonCallFriend();
        void pushButtonFriendList();
        void OnFailedFriendRequest();
        void OnSuccessFriendRequest();
        void OnFriendDoubleClicked();

        void OnSuccessFriendDeletion();
        void OnFailedFriendDeletion();

        void OnFailedLogOutRequest();
        void OnSuccessLogOutRequest();

        void OnReceiveFriendRequest();

        void OnFriendAcceptedRequest();

        void OnSuccessAcceptFriendRequest();
        void OnFailedAcceptFriendRequest();

        void OnSuccessCallRequest();
        void OnFailedCallRequest();

        void OnCallAcceptRequest();

        void OnCallAcceptedRequest();

        void OnSuccessCallAcceptRequest();
        void OnFailedCallAcceptRequest();

        void OnSuccessDeleteRequest();
        void OnFailedDeleteRequest();

    private:
        std::string toDelete;
        std::string toAdd;
        std::string toCall;
        bool listTrigger;
        bool initFriendList;
        QtUserInterface *win;
        //QListWidget *List;
        QLineEdit *adder;
        std::vector<std::string> friendList;
        Sender s;
        Receiver r;

};


#endif /* !MAINPAGE_HPP_ */
