#include "transaction.h"

#include "db_constants.h"

namespace app::db1
{

void Transaction::beginTransaction()
{
    switch (m_db.m_type) {
    case DatabaseType::SQLITE:
    {
        if (SQLiteConnection* sqliteConn = dynamic_cast<SQLiteConnection*>(m_db.m_connection.get()))
        {
            SQLiteQuery begin_transaction(*sqliteConn, consts::SQLConsts::begin_transaction);
        }
        else
        {
            throw std::runtime_error("");
        }
    }
    break;
    default:
        throw std::runtime_error("");
    }
}

void Transaction::endTransaction()
{
    switch (m_db.m_type) {
    case DatabaseType::SQLITE:
    {
        if (SQLiteConnection* sqliteConn = dynamic_cast<SQLiteConnection*>(m_db.m_connection.get()))
        {
            SQLiteQuery end_transaction(*sqliteConn, consts::SQLConsts::end_transaction);
        }
        else
        {
            throw std::runtime_error("");
        }
    }
    break;
    default:
        throw std::runtime_error("");
    }
}

void Transaction::commit()
{
    switch (m_db.m_type) {
    case DatabaseType::SQLITE:
    {
        if (SQLiteConnection* sqliteConn = dynamic_cast<SQLiteConnection*>(m_db.m_connection.get()))
        {
            SQLiteQuery commit(*sqliteConn, consts::SQLConsts::commit);
        }
        else
        {
            throw std::runtime_error("");
        }
    }
    break;
    default:
        throw std::runtime_error("");
    }
}

void Transaction::rollback()
{
    switch (m_db.m_type) {
    case DatabaseType::SQLITE:
    {
        if (SQLiteConnection* sqliteConn = dynamic_cast<SQLiteConnection*>(m_db.m_connection.get()))
        {
            SQLiteQuery rollback(*sqliteConn, consts::SQLConsts::rollback);
        }
        else
        {
            throw std::runtime_error("");
        }
    }
    break;
    default:
        throw std::runtime_error("");
    }
}

} // namespace app::db1
