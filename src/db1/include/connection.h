#pragma once

#include <sqlite3.h>

#include <cstring>
#include <string>

#include <mutex>

namespace app::db1
{

class IConnection
{
public:
    virtual bool tryConnect(const std::string& path) = 0;
    virtual bool tryConnect() = 0;
    virtual bool disconnect() = 0;

    virtual void setPath(const std::string& path) = 0;
    virtual std::string getPath() const = 0;
};

struct SQLiteQuery;

class SQLiteConnection : public IConnection
{
public:
    friend struct SQLiteQuery;

    SQLiteConnection();
    ~SQLiteConnection();

    SQLiteConnection(const SQLiteConnection&) = delete;
    SQLiteConnection(SQLiteConnection&&) = delete;
    SQLiteConnection& operator = (const SQLiteConnection&) = delete;
    SQLiteConnection& operator = (SQLiteConnection&&) = delete;

    bool exec(std::string&& query, sqlite3_stmt** result = NULL);
    bool tryConnect(const std::string& path) override;
    bool tryConnect() override;
    bool disconnect() override;

    void setPath(const std::string& path) override;
    std::string getPath() const override;

private:
    mutable std::recursive_mutex sync;
    bool isConnected = false;
    std::string db_Path{ "" };
    sqlite3* pDb = 0;

};

} // namespace app::database
