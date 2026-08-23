#pragma once

#include <DAO.h>
#include <stdexcept>

#include <memory>

namespace app::db2
{

class SQLiteDB
{
    friend class Transaction;

private:
    sqlite3* _db;
    bool _isOpen;

public:
    SQLiteDB();

    bool open();
    void close();

    bool generateDB();

    template<typename T>
    std::shared_ptr<IDAO<T>> getDAO()
    {
        if constexpr (std::same_as<T, UserDTO>)
            return std::make_shared<UserDAO>(_db);
        else
            throw std::runtime_error("DAO for this type is not implemented");
    }

};

} // app::db2
