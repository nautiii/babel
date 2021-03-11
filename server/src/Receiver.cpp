/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Receiver.cpp
*/

#include "Receiver.hpp"

Receiver::Receiver(size_t size)
    : _uncomplete(false)
{
    _size = size;
    _data = new char[_size];
}

Receiver::~Receiver()
{
    delete[] _data;
}

void Receiver::clear() noexcept
{
    _len = 0;
    _pkg.magic = 0;
    _pkg.snder = 0;
    _pkg.rcver = 0;
    _pkg.cmd = static_cast<Request>(0);
    _pkg.args.clear();
}

ClientPackage Receiver::deserialize()
{
    if (_uncomplete) {
        _pkg.args += _data;
    } else {
        clear();

        array<bitset<8>, 4> magic_part = { bitset<8>(static_cast<unsigned long long>(_data[3])), bitset<8>(static_cast<unsigned long long>(_data[2])), bitset<8>(static_cast<unsigned long long>(_data[1])), bitset<8>(static_cast<unsigned long long>(_data[0])) };
        array<bitset<8>, 4> snder_part = { bitset<8>(static_cast<unsigned long long>(_data[7])), bitset<8>(static_cast<unsigned long long>(_data[6])), bitset<8>(static_cast<unsigned long long>(_data[5])), bitset<8>(static_cast<unsigned long long>(_data[4])) };
        array<bitset<8>, 4> rcver_part = { bitset<8>(static_cast<unsigned long long>(_data[11])), bitset<8>(static_cast<unsigned long long>(_data[10])), bitset<8>(static_cast<unsigned long long>(_data[9])), bitset<8>(static_cast<unsigned long long>(_data[8])) };
        array<bitset<8>, 4> cmd_part   = { bitset<8>(static_cast<unsigned long long>(_data[15])), bitset<8>(static_cast<unsigned long long>(_data[14])), bitset<8>(static_cast<unsigned long long>(_data[13])), bitset<8>(static_cast<unsigned long long>(_data[12])) };
        array<bitset<8>, 4> size_part  = { bitset<8>(static_cast<unsigned long long>(_data[19])), bitset<8>(static_cast<unsigned long long>(_data[18])), bitset<8>(static_cast<unsigned long long>(_data[17])), bitset<8>(static_cast<unsigned long long>(_data[16])) };
        array<int *, 5> fields = { &_pkg.magic, &_pkg.snder, &_pkg.rcver, reinterpret_cast<int *>(&_pkg.cmd), reinterpret_cast<int *>(&_len) };
        array<array<bitset<8>, 4>, 5> parts = { move(magic_part), move(snder_part), move(rcver_part), move(cmd_part), move(size_part) };

        for (size_t z(0); z < parts.size(); z++) {
            bitset<32> tmp(0);
            for (size_t a(0), b(0); a < parts[z].size(); a++) {
                for (size_t c(0); c < parts[z][a].size(); c++, b++)
                    if (parts[z][a].test(c))
                        tmp.set(b);
            }
            *(fields[z]) = tmp.to_ulong();
        }
        _pkg.args = &_data[20];
    }
    
    if (_pkg.args.length() == _len - 1) {
        _uncomplete = false;
        return _pkg;
    }
    _uncomplete = true;
    return nullpkg;
}
