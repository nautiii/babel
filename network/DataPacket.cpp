/*
** EPITECH PROJECT, 2020
** B-CPP-500-PAR-5-1-babel-thomas.raveneau
** File description:
** DataPacket
*/

#include "DataPacket.hpp"
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>

DataPacket::DataPacket(int cmd, char *arg)
{
    if (!cmd || !arg)
        return;
    this->arg = arg;
    this->cmd = cmd;
}

DataPacket::~DataPacket()
{
}

protocol::Response DataPacket::extractResponse() {
    return static_cast<protocol::Response>(cmd);
}

std::vector<std::string> DataPacket::extractData()
{
    std::string s(arg);
    std::vector<std::string> parsedData;
    std::replace(s.begin(), s.end(), ':', ' ');
    std::stringstream ss(s);
    std::string tmp;

    while (!ss.eof()) {
        ss >> tmp;
        parsedData.push_back(tmp);
        tmp.clear();
    }
    return parsedData;
}



