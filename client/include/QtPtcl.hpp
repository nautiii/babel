/*
** EPITECH PROJECT, 2020
** B-CPP-500-PAR-5-1-babel-thomas.raveneau
** File description:
** QtPtcl
*/

#ifndef QTPTCL_HPP_
#define QTPTCL_HPP_

#include "Protocol.hpp"

#include <string>
#include <QtCore/QObject>
#include <QtCore/QDataStream>
#include <QtNetwork/QTcpSocket>

using namespace std;

namespace protocol
{
    namespace qt
    {
        struct QtPackage : public Package<Request, string>
        {
            QByteArray serialize()
            {
                QByteArray byteArray;
                QDataStream stream(&byteArray, QIODevice::WriteOnly);
            
                stream << magic
                        << snder
                        << rcver
                        << cmd
                        << args.c_str();
            
                return byteArray;
            }

            void deserialize(QByteArray byteArray)
            {
                QDataStream stream(&byteArray, QIODevice::ReadOnly);
                char *tmp;
                int test;

                stream >> magic
                        >> snder
                        >> rcver
                        >> test
                        >> tmp;

                cmd = (protocol::Request) test;
            }

            void reset()
            {
                magic = 0;
                snder = 0;
                rcver = 0;
                args.clear();
            }
        };
    }
}

#endif /* !QTPTCL_HPP_ */
