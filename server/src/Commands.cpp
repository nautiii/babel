/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Commands.cpp
*/

#include "Commands.hpp"

bool Commands::isAlphaNum(const string &s) const
{
    return find_if(s.begin(), s.end(), 
        [](char c) { 
            return !(isalnum(c) || c == ' ');
        }
    ) == s.end();
}

bool Commands::missingArgs(const size_t &size, const vector<string> &args) const
{

    if (args.size() < size)
        return true;
    for (const auto &i : args)
        if (i.empty())
            return true;
    return false;
}