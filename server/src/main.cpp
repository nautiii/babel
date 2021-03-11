/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** main.cpp
*/

#include "Server.hpp"

int main(int, const char **av)
{
    try {
        AsioServer s(av);

        s.run();
    } catch (exception &e) {
        cerr << "error: " << e.what() << endl;
    }
}
