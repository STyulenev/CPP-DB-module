#include "connection.h"

namespace app::db1
{

SQLiteConnection::SQLiteConnection()
{

}

SQLiteConnection::~SQLiteConnection()
{
    try
    {
        if (NULL != pDb)
        {
            sqlite3_close(pDb);
        }
    }
    catch (...)
    {

    }
}

bool SQLiteConnection::exec(std::string&& query, sqlite3_stmt** result)
{
    return SQLITE_OK == sqlite3_prepare_v2(pDb, query.c_str(), -1, result, NULL);
}

bool SQLiteConnection::tryConnect(const std::string& path)
{
    std::scoped_lock lock(sync);
    db_Path = path;
    isConnected = sqlite3_open_v2(db_Path.data(), &pDb, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL) == SQLITE_OK;

    return isConnected;
}

bool SQLiteConnection::tryConnect()
{
    std::scoped_lock lock(sync);
    isConnected = sqlite3_open_v2(db_Path.data(), &pDb, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL) == SQLITE_OK;

    return isConnected;
}

bool SQLiteConnection::disconnect()
{
    std::scoped_lock lock(sync);

    if (pDb)
    {
        int result = sqlite3_close_v2(pDb); // или sqlite3_close для старых версий
        if (result == SQLITE_OK)
        {
            pDb = nullptr;
            isConnected = false;
            return true;
        }
        else
        {
            return false;
        }
    }

    return true;
}

void SQLiteConnection::setPath(const std::string& path)
{
    db_Path = path;
}

std::string SQLiteConnection::getPath() const
{
    return db_Path;
}

} // namespace app::db1
