#pragma once

#include "db.h"

namespace app::db1
{

class Transaction final
{
public:
    template<typename Lambda>
    Transaction(Db& _db, bool& status, Lambda&& lambda) : m_db{ _db }
    {
        status = false;
        std::lock_guard lock(m_db.m_sync);

        try
        {
            beginTransaction();
            lambda();
            endTransaction();
            //commit();
            status = true;
            return;
        }
        catch (...)
        {

        }

        try
        {
            rollback();
        }
        catch (...)
        {

        }

        throw std::runtime_error("");
    }

    void beginTransaction();
    void endTransaction();
    void commit();
    void rollback();

private:
    Db& m_db;

};

} // namespace app::db1
