#pragma once

#include <DAO.h>
#include <stdexcept>


namespace app::db2
{

class IDB
{
    friend class Transaction;

public:
    virtual bool open() = 0;
    virtual void close() = 0;

    virtual bool generateDB() = 0;

};

class SQLiteDB : public IDB
{
    friend SQLiteQuery;

private:
    sqlite3* _db;
    bool _isOpen;

public:
    SQLiteDB();

    bool open() override;
    void close() override;

    bool generateDB() override;

};

template<typename T>
std::shared_ptr<IDAO<T>> getDAO(const std::shared_ptr<IDB>& idb)
{
    if constexpr (std::same_as<T, UserDTO>)
        return std::make_shared<UserDAO>(idb);
    else
        throw std::runtime_error("DAO for this type is not implemented");
}

} // app::db2
