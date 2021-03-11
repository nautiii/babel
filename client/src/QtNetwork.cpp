/*
** EPITECH PROJECT, 2020
** *
** File description:
** QtNetwork
*/

#include <bitset>

#include "QtNetwork.hpp"
#include "QtUserInterface.hpp"

using namespace client::networkManager::qt;
using namespace std;

QtNetwork::QtNetwork(string ip, int port, QtUserInterface *vwindow) : ANetworkManager(ip, port, vwindow), _socket(new QTcpSocket())
{
    QObject::connect(_socket, SIGNAL(readyRead()), this, SLOT(receive()));
}

QtNetwork::~QtNetwork()
{
}

void QtNetwork::connectSocket()
{
    _socket->connectToHost(_ip.c_str(), (quint16) _port);

    if (_socket->waitForConnected(3000)) {
        cout << "Client connected" << endl;
        _isConnected = true;
    } else
        cout << "ERROR: Client couldn't connect to server, check if the server is running" << endl;    
}

void QtNetwork::disconnectSocket()
{
    if (_isConnected) {
        _socket->disconnectFromHost();
        cout << "Client disconnected" << endl;
        _isConnected = false;
    }
    else
        cout << "ERROR: Client must me connected to be able to disconnect from the server" << endl;
}

const QtPackage QtNetwork::makePackage(Request req, string args) const noexcept
{
    return QtPackage {
        MAGIC,
        _port,
        _socket->peerPort(),
        req,
        args
    };
}

void QtNetwork::send(Request req, string args)
{
    if (!_isConnected)
        return;

    QtPackage pkg = makePackage(req, args);
    QByteArray arr = pkg.serialize();

    int res = _socket->write(arr);
    _socket->waitForBytesWritten();
}

void QtNetwork::receive()
{
    if (!_isConnected)
        return;
    if (!_socket->isReadable())
        return;

    QByteArray byteArray = _socket->readAll();
    const auto c = &byteArray.data()[5];
    char *args = &c[24];

    array<bitset<8>, 4> arr = {bitset<8>((unsigned long long)c[0]), bitset<8>((unsigned long long)c[1]), bitset<8>((unsigned long long)c[2]), bitset<8>((unsigned long long)c[3])};
    array<bitset<8>, 4> brr = {bitset<8>((unsigned long long)c[4]), bitset<8>((unsigned long long)c[5]), bitset<8>((unsigned long long)c[6]), bitset<8>((unsigned long long)c[7])};
    array<bitset<8>, 4> crr = {bitset<8>((unsigned long long)c[8]), bitset<8>((unsigned long long)c[9]), bitset<8>((unsigned long long)c[10]), bitset<8>((unsigned long long)c[11])};
    array<bitset<8>, 4> drr = {bitset<8>((unsigned long long)c[12]), bitset<8>((unsigned long long)c[13]), bitset<8>((unsigned long long)c[14]), bitset<8>((unsigned long long)c[15])};

    bitset<32> bits;
    int b = 0;
    for (auto i : arr) {
        for (int j(0); j < i.size(); j++, b++) {
            if (i.test(j))
                bits.set(b);
        }
    }
    bitset<32> bbits;
    int ca = 0;
    for (auto i : brr) {
        for (int j(0); j < i.size(); j++, ca++) {
            if (i.test(j))
                bbits.set(ca);
        }
    }
    bitset<32> cbits;
    int pa = 0;
    for (auto i : crr) {
        for (int j(0); j < i.size(); j++, pa++) {
            if (i.test(j))
                cbits.set(pa);
        }
    }
    bitset<32> dbits;
    int qa = 0;
    for (auto i : drr) {
        for (int j(0); j < i.size(); j++, qa++) {
            if (i.test(j))
                dbits.set(qa);
        }
    }
    _vwindow->receiveDataPacket(DataPacket(dbits.to_ulong(), args));
}

