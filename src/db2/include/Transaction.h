#pragma once

#include "Database.h"

namespace app::db2
{

class Transaction final
{
public:
    template<typename Lambda>
    Transaction(SQLiteDB& _db, bool& status, Lambda&& lambda) : m_db{ _db }
    {
        status = false;

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
    SQLiteDB& m_db;

};

} // namespace app::db2
