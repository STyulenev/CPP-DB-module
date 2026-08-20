#include "Database.h"

namespace app::db2
{

SQLiteDB::SQLiteDB() :
    _db(nullptr),
    _isOpen(false)
{

}

bool SQLiteDB::open()
{
    _isOpen = (sqlite3_open("test.db", &_db) == SQLITE_OK);
    return _isOpen;
}

void SQLiteDB::close()
{
    if (_isOpen)
    {
        sqlite3_close(_db);
    }
}

bool SQLiteDB::generateDB()
{
    try
    {
        char* messaggeError;

        const int status = sqlite3_exec(_db, UserDTO::createTableScript.c_str(), nullptr, 0, &messaggeError);

        if (status != SQLITE_OK)
        {
            //qDebug() << "Error:" << std::string(messaggeError);
            sqlite3_free(messaggeError);

            return false;
        }
        else
        {
            return true;
        }
    }
    catch (...)
    {
        return false;
    }

    return true;
}

} // namespace app::db2
