#include "Query.h"

#include "Database.h"

#include <iostream>
#include <stdexcept>

namespace app::db2
{

IQuery::IQuery(const std::string& queryStr) :
    _queryStr(queryStr)
{

}

SQLiteQuery::SQLiteQuery(SQLiteDB* idb, const std::string& queryStr) :
    IQuery(queryStr),
    _db(idb),
    stmt(nullptr)
{

}

void SQLiteQuery::prepare()
{
    int status = sqlite3_prepare_v2(_db->_db, _queryStr.c_str(), -1, &stmt, nullptr);

    if (status != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(_db->_db) << "\n";
        throw std::runtime_error("Query error");
    }

    status = sqlite3_step(stmt);

    if (status == SQLITE_ROW)
    {
        // Это SELECT-запрос
        return;
    }
    else if (status == SQLITE_DONE)
    {
        // Успех
        sqlite3_finalize(stmt);
        return;
    }
    else
    {
        // Ошибка выполнения
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(_db->_db) << "\n";
        sqlite3_finalize(stmt);
        throw std::runtime_error("Query error");
    }
}

void SQLiteQuery::exec()
{
    const int status = sqlite3_exec(_db->_db, _queryStr.c_str(), nullptr, nullptr, nullptr);

    if (status != SQLITE_OK)
    {
        throw std::runtime_error("Query error");
    }
}

void SQLiteQuery::parse(std::vector<UserDTO>& results)
{
    if (!stmt)
    {
        throw std::runtime_error("Query error");
    }

    do
    {
        if (sqlite3_data_count(stmt) > 0)
        {
            UserDTO user;

            user.id = std::stoi((char *)sqlite3_column_text(stmt, UserDTO::RowFields::ID));
            user.name = std::string((char *)sqlite3_column_text(stmt, UserDTO::RowFields::NAME));

            results.push_back(user);
        }
    }
    while (sqlite3_step(stmt) == SQLITE_ROW);

    sqlite3_finalize(stmt);
}

std::shared_ptr<IQuery> getQuery(const std::shared_ptr<IDB> &idb, const std::string &queryStr)
{
    if (SQLiteDB* _db = dynamic_cast<SQLiteDB*>(idb.get()))
    {
        return std::make_shared<SQLiteQuery>(_db, queryStr);
    }
    else
    {
        throw std::runtime_error("Query error Capability Query");
    }

    throw std::runtime_error("Query error Capability Query");
}

} // namespace app::db2
