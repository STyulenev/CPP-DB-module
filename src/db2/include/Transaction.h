#pragma once

#include "Database.h"

namespace app::db2
{

class Transaction final
{
public:
    template<typename Lambda>
    Transaction(std::shared_ptr<IDB>& _db, bool& status, Lambda&& lambda) : m_db{ _db }
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

private:
    void beginTransaction();
    void endTransaction();
    void commit();
    void rollback();

private:
    std::shared_ptr<IDB> m_db;

};

} // namespace app::db2
