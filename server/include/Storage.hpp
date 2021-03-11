/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Storage.hpp
*/

#ifndef STORAGE_HPP_
# define STORAGE_HPP_

#include <sqlite3.h>
#include <iostream>
#include <tuple>
#include <algorithm>

#include "Exception.hpp"
#include "IStorage.hpp"

# define SQLDB_NAME "babel.db"

using namespace std;

namespace server
{
    namespace storage
    {
        class SQLite : public IStorage
        {
            public:
                SQLite();
                ~SQLite();
            private:
                void error(char *err, SQLiteException::Flag f) const;
            public:
                bool exist(const string &name) const final;
                bool isOnline(const string &name) const final;
                const string getPassword(const string &name) const final;
                vector<string> getRelations(const string &name) const final;
                void addClient(const string &usr, const string &pass) const final;
                void addRelation(const string &usrA, const string &usrB) const final;
                void delRelation(const string &usrA, const string &usrB) const final;
                void connect(const string &usr, bool co=true) const final;
            private:
                sqlite3 *_db;
        };
    }
}

using namespace server::storage;

#endif /* !STORAGE_HPP_ */
