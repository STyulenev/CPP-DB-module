#pragma once

#include <sqlite3.h>
#include <vector>
#include <memory>

#include "DTO.h"

namespace app::db2
{

class IDB;
class SQLiteDB;

class IQuery
{
public:
    IQuery() = delete;
    IQuery(IDB* idb, const std::string& queryStr);

    virtual void prepare() = 0;
    virtual void exec() = 0;

    virtual void parse(std::vector<UserDTO>& results) = 0;

protected:
    IDB* _db;
    std::string _queryStr;

};

class SQLiteQuery final : public IQuery
{
public:
    SQLiteQuery() = delete;
    SQLiteQuery(SQLiteDB* idb, const std::string& queryStr);

    void prepare() override;
    void exec() override;

    void parse(std::vector<UserDTO>& results) override;

private:
    sqlite3_stmt* stmt;
};

std::shared_ptr<IQuery> getQuery(const std::shared_ptr<IDB>& idb, const std::string& queryStr);

} // namespace app::db2
