/*
** EPITECH PROJECT, 2020
** B-CPP-500-PAR-5-1-babel-thomas.raveneau
** File description:
** QtUdpNetwork
*/

#ifndef QTUDPNETWORK_HPP_
#define QTUDPNETWORK_HPP_

#include <QtCore/QCoreApplication>
#include <QtCore/QObject>
#include <QtNetwork/QUdpSocket>

#include <string>
#include <iostream> 
#include <sstream>
#include <vector>
#include <cstring>

#include "PortAudio.hpp"

class Sender : public QObject
{
    Q_OBJECT
public:
    explicit Sender(quint16 port, QObject *parent = 0);
    client::audioManager::portAudio::PortAudio audio;
    void send(std::string ip, quint16 port, std::vector<uint16_t *> to_send);
private:
    QUdpSocket *socket;
};

class Receiver : public QObject
{
    Q_OBJECT
public:
    explicit Receiver(quint16 port, QObject *parent = 0);
    client::audioManager::portAudio::PortAudio audio;
signals:
public slots:
    void readyRead();
private:
    QUdpSocket *socket;
};

#endif /* !QTUDPNETWORK_HPP_ */
