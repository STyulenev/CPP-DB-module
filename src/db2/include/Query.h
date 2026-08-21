#pragma once

#include <sqlite3.h>
#include <vector>

#include "DTO.h"

namespace app::db2
{

class Query
{
public:
    Query() = delete;
    Query(sqlite3* db, const std::string& queryStr);

    void parse(std::vector<UserDTO>& results);

private:
    sqlite3* _db;
    sqlite3_stmt* stmt;
    std::string _queryStr;
};

} // namespace app::db2
