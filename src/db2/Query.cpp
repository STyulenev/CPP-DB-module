#include "Query.h"

#include <iostream>
#include <stdexcept>

namespace app::db2
{

Query::Query(sqlite3* db, const std::string& queryStr) :
    _db(db),
    stmt(nullptr),
    _queryStr(queryStr)
{
    int rc = sqlite3_prepare_v2(_db, _queryStr.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(_db) << "\n";
        throw std::runtime_error("Query error");
    }

    rc = sqlite3_step(stmt);

    if (rc == SQLITE_ROW)
    {
        // Это SELECT-запрос
        return;
    }
    else if (rc == SQLITE_DONE)
    {
        // Успех
        sqlite3_finalize(stmt);
        return;
    }
    else
    {
        // Ошибка выполнения
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(_db) << "\n";
        sqlite3_finalize(stmt);
        throw std::runtime_error("Query error");
    }
}

void Query::parse(std::vector<UserDTO>& results)
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

} // namespace app::db2
