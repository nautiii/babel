/*
** EPITECH PROJECT, 2020
** B-CPP-500-PAR-5-1-babel-thomas.raveneau
** File description:
** QtNetwork
*/

#ifndef QTNETWORK_HPP_
#define QTNETWORK_HPP_

#include <QtCore/QObject>
#include <QtNetwork/QTcpSocket>
#include "QtPtcl.hpp"

#include "ANetworkManager.hpp"

class QtUserInterface;

using namespace protocol::qt;

namespace client {

    namespace networkManager {

        namespace qt {

            class QtNetwork : public QObject, public ANetworkManager<QtUserInterface, QTcpSocket, QtPackage> {
                Q_OBJECT
                public:
                    QtNetwork(string ip, int port, QtUserInterface *vwindow);
                    ~QtNetwork();
                    
                    void connectSocket();
                    void disconnectSocket();

                    const QtPackage makePackage(Request req, string args) const noexcept;

                    void send(Request req, string args);

                    void connectUdp();



                private slots:
                    void receive();

                protected:
                    QTcpSocket *_socket;
                    QtPackage _pkg;
            };

        }

    }

}

#endif /* !QTNETWORK_HPP_ */
