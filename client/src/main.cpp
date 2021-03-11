/*
** EPITECH PROJECT, 2020
** B-CPP-500-PAR-5-1-babel-thomas.raveneau
** File description:
** main
*/

#include "Client.hpp"
#include "QtUdpNetwork.hpp"
#include "PortAudio.hpp"

using namespace client;

// int main()
// {
//     client::audioManager::portAudio::PortAudio pa;
//     vector<uint16_t *> buff;

//     pa.InitInput();
//     pa.InitOutput();
//     pa.OpenStream();

//     while (true) {
//         buff = pa.Write(buff);
//         pa.Read(buff);
//     }
//     pa.StopStream();
// }

// #include <fstream>

int main(int ac, char **av)
{
    // int status = std::system("curl myexternalip.com/raw > ip");
    // std::ifstream ifs("ip");
    // std::string content;
    // content.assign(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());

    if (ac < 2)
        return (84);
    QApplication app(ac, av);
    Client *client = new Client(av[1], (ac > 2) ? stoi(av[2]) : 8080, ac, av);

    client->run();
    app.exec();
}

// Sender::Sender(quint16 port, QObject *parent) : QObject(parent)
// {
//     socket = new QUdpSocket(this);
//     cout << ((socket->bind(QHostAddress("192.168.1.78"), port)) ? "socket bind to port " : "failed to bind ") << socket->localPort() << endl;
// }

// Receiver::Receiver(quint16 port, QObject *parent) : QObject(parent)
// {
//     socket = new QUdpSocket(this);
//     cout << ((socket->bind(QHostAddress::Any, port)) ? "socket bind to port " : "failed to bind ") << socket->localPort() << endl;
//     connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
// }

// void Sender::HelloUDP()
// {
//     QHostAddress addr("86.246.181.227");
//     const auto len = socket->writeDatagram("Hello from UDP", 14, addr, 8081);

//     cout << "wrote " << len << " bytes\n";
//     if (len < 0)
//         cerr << socket->errorString().toStdString() << endl;
// }

// void Receiver::readyRead()
// {
//     QByteArray buffer;
//     QHostAddress sender;
//     quint16 senderPort;

//     buffer.resize(socket->pendingDatagramSize());
//     socket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);

//     cout << "Message from: " << sender.toString().toStdString() << endl;
//     cout << "Message port: " << senderPort << endl;
//     cout << "Message: " << buffer.data() << endl;
// }

// int main(int argc, char *argv[])
// {
//     QApplication a(argc, argv);
//     Sender c(0);
//     Receiver r(8081);

//     c.HelloUDP();
//     return a.exec();
// }
