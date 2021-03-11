/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** Storage.cpp
*/

#include "Storage.hpp"

SQLite::SQLite()
{
    char *err = NULL;

    if (sqlite3_open(SQLDB_NAME, &_db) ^ SQLITE_OK)
        throw SQLiteException(SQLiteException::UNDEFINED);

    int res = sqlite3_exec(_db,
        "CREATE TABLE client("                     \
        "id             INTEGER PRIMARY KEY,"      \
        "pseudo         CHAR(32) UNIQUE NOT NULL," \
        "password       CHAR(32)        NOT NULL," \
        "online         INTEGER);"                 \
        "CREATE TABLE relation("                   \
        "userA          CHAR(32) NOT NULL,"        \
        "userB          CHAR(32) NOT NULL,"        \
        "UNIQUE(userA, userB));"                   \
        , nullptr, 0, &err
    );

    if (res ^ SQLITE_OK && res ^ SQLITE_ERROR)
        error(err, SQLiteException::TABLE);
}

SQLite::~SQLite()
{
    if (sqlite3_close(_db) ^ SQLITE_OK)
        cout << "sqlite connection to '" << SQLDB_NAME << "'didn't close correctly" << endl;
    cout << "sqlite connection to '" << SQLDB_NAME << "' closed" << endl;
}

void SQLite::error(char *err, SQLiteException::Flag f) const
{
    cerr << err << endl;
    sqlite3_free(err);

    throw SQLiteException(f);
}

bool SQLite::exist(const string &name) const
{
    char *err = NULL;
    tuple<const string, bool> infos = make_tuple(name.c_str(), false);
    const string stmt = "SELECT pseudo FROM client";

    int res = sqlite3_exec(_db, stmt.c_str(),
        [](void *ptr, int n, char **val, char **) {
            const string name = get<0>(*reinterpret_cast<tuple<const string, bool> *>(ptr));

            for (int i(0); i < n; ++i)
                if (name == val[i]) {
                    get<1>(*reinterpret_cast<tuple<const string, bool> *>(ptr)) = true;
                    return 0;
                }
            return 0;
        },
        reinterpret_cast<void *>(&infos), &err
    );

    if (res ^ SQLITE_OK)
        error(err, SQLiteException::EXIST);
    return get<1>(infos);
}

bool SQLite::isOnline(const string &name) const
{
    char *err = NULL;
    int online = -1;
    const string stmt = "SELECT online FROM client WHERE pseudo='" + name + "';";
        
    int res = sqlite3_exec(_db, stmt.c_str(),
        [](void *online, int, char **val, char **) {
            *reinterpret_cast<int *>(online) = stoi(val[0]);
            return 0;
        },
        reinterpret_cast<void *>(&online), &err
    );

    if (res ^ SQLITE_OK)
        error(err, SQLiteException::ONLINE);
    if (online < 0)
        throw SQLiteException(SQLiteException::ONLINE);
    return online;
}

const string SQLite::getPassword(const string &name) const
{
    char *err = NULL;
    string pass;
    const string stmt = "SELECT password FROM client WHERE pseudo='" + name + "';";

    int res = sqlite3_exec(_db, stmt.c_str(),
        [](void *pass, int, char **val, char **) {
            *reinterpret_cast<string *>(pass) = val[0];
            return 0;
        },
        reinterpret_cast<void *>(&pass), &err
    );

    if (res ^ SQLITE_OK)
        error(err, SQLiteException::PASSWORD);
    return pass;
}

vector<string> SQLite::getRelations(const string &name) const
{
    char *err = NULL;
    vector<string> list;
    const string stmt = "SELECT * FROM relation WHERE userA='" + name + "' OR userB='" + name + "';";

    int res = sqlite3_exec(_db, stmt.c_str(),
        [](void *list, int, char **val, char **) {
            reinterpret_cast<vector<string> *>(list)->push_back(val[0]);
            reinterpret_cast<vector<string> *>(list)->push_back(val[1]);
            return 0;
        },
        reinterpret_cast<vector<string> *>(&list), &err
    );

    if (res ^ SQLITE_OK)
        error(err, SQLiteException::ONLINE);
    
    for (vector<string>::iterator it = list.begin(); it != list.end(); ) {
        if ((*it) == name)
            it = list.erase(it);
        else
            ++it;
    }
    return list;
}

void SQLite::addClient(const string &usr, const string &pass) const
{
    char *err = NULL;
    const string stmt = "INSERT INTO client(pseudo, password, online) VALUES ('" + usr + "','" + pass + "',1);";

    int res = sqlite3_exec(_db, stmt.c_str(),
        [](void *, int, char **, char **) {
            return 0;
        },
        nullptr, &err
    );

    if (res ^ SQLITE_OK)
        error(err, SQLiteException::INSERT);
}

void SQLite::addRelation(const string &usrA, const string &usrB) const
{
    char *err = NULL;
    const string stmt = "INSERT INTO relation VALUES ('" + usrA + "','" + usrB + "');";

    int res = sqlite3_exec(_db, stmt.c_str(),
        [](void *, int, char **, char **) {
            return 0;
        },
        nullptr, &err
    );

    if (res ^ SQLITE_OK)
        error(err, SQLiteException::RELATION);
}

void SQLite::delRelation(const string &usrA, const string &usrB) const
{
    char *err = NULL;
    const string stmt = "DELETE FROM relation WHERE (userA='" + usrA + "' AND userB='" + usrB + "') OR (userA='" + usrB + "' AND userB='" + usrA + "');";

    int res = sqlite3_exec(_db, stmt.c_str(),
        [](void *, int, char **, char **) {
            return 0;
        },
        nullptr, &err
    );

    if (res ^ SQLITE_OK)
        error(err, SQLiteException::DELREL);
}

void SQLite::connect(const std::string &usr, bool co) const
{
    char *err = NULL;
    const string stmt = "UPDATE client SET online=" + to_string(static_cast<int>(co)) + " WHERE pseudo='" + usr + "';";

    int res = sqlite3_exec(_db, stmt.c_str(),
        [](void *, int, char **, char **) {
            return 0;
        },
        nullptr, &err
    );

    if (res ^ SQLITE_OK)
        error(err, SQLiteException::LOG);
}
