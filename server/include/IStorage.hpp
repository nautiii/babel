/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** IStorage.hpp
*/

#ifndef ISTORAGE_HPP_
# define ISTORAGE_HPP_

#include <string>
#include <vector>

namespace server
{
    namespace storage
    {
        class IStorage
        {
            public:
                virtual ~IStorage() = default;
            public:
                virtual bool exist(const std::string &name) const = 0;
                virtual bool isOnline(const std::string &name) const = 0;
                virtual const std::string getPassword(const std::string &name) const = 0;
                virtual std::vector<std::string> getRelations(const std::string &name) const = 0;
                virtual void addClient(const std::string &usr, const std::string &pass) const = 0;
                virtual void addRelation(const std::string &usrA, const std::string &usrB) const = 0;
                virtual void delRelation(const std::string &usrA, const std::string &usrB) const = 0;
                virtual void connect(const std::string &usr, bool co=true) const = 0;
        };
    }
}

#endif /* !ISTORAGE_HPP_ */
