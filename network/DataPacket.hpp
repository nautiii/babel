/*
** EPITECH PROJECT, 2020
** B-CPP-500-PAR-5-1-babel-thomas.raveneau
** File description:
** DataPacket
*/

#ifndef DATAPACKET_HPP_
#define DATAPACKET_HPP_

#include <QObject>
#include <Protocol.hpp>

#define parseSeparator ':'

class DataPacket : public QObject{
    Q_OBJECT

    public:
        DataPacket(int cmd, char *arg);
        ~DataPacket();
        protocol::Response extractResponse();
        std::vector<std::string> extractData();
    private:
        int cmd;
        char *arg;
};
#endif /* !DATAPACKET_HPP_ */
