/*
** EPITECH PROJECT, 2020
** B-CPP-500-PAR-5-1-babel-thomas.raveneau
** File description:
** QtUdpNetwork
*/

#include "QtUdpNetwork.hpp"

Sender::Sender(quint16 port, QObject *parent)
    : QObject(parent), audio()
{
    socket = new QUdpSocket(this);
    cout << ((socket->bind(QHostAddress("192.168.1.78"), port)) ? "socket bind to port " : "failed to bind ") << socket->localPort() << endl;
}

void Sender::send(std::string ip, quint16 port, std::vector<std::uint16_t *> to_send)
{
    QHostAddress addr(ip.c_str());
    char *ptr = reinterpret_cast<char *>(to_send[0]);
    const auto len = socket->writeDatagram(ptr, 480 * sizeof(uint16_t), addr, port);

    // cout << "wrote " << len << " bytes\n";
    if (len < 0)
        cerr << socket->errorString().toStdString() << endl;
}

Receiver::Receiver(quint16 port, QObject *parent)
    : QObject(parent), audio()
{
    socket = new QUdpSocket(this);
    cout << ((socket->bind(QHostAddress::Any, port)) ? "socket bind to port " : "failed to bind ") << socket->localPort() << endl;
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void Receiver::readyRead()
{
    QByteArray buffer;
    QHostAddress sender;
    quint16 senderPort;

    buffer.resize(socket->pendingDatagramSize());
    if (buffer.size() == 0)
        return ;
    socket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);

    uint16_t *y = reinterpret_cast<uint16_t *>(std::malloc(buffer.size()));
    std::memcpy(y, buffer.constData(), buffer.size());
// std::memset(y, 0, buffer.size());
//     cout << "Message from: " << sender.toString().toStdString() << endl;
//     cout << "Message port: " << senderPort << endl;

    // std::vector<u_int16_t *> buff;
    audio.writeThis(y);

    // cout << "==========" << endl;
    // for (int i = 0; i < buffer.size(); i++)
    //     cout << y[i];
    // cout << endl;

    // for (int i = 0; i < buffer.size(); i++)
    //     x[0][i] = y[i];

    audio.Read(y);
    std::free(y);
}