#pragma once

#include "db.h"

namespace app::database
{

class Transaction final
{
public:
    template<typename Lambda>
    Transaction(Db& _db, bool& bRet, Lambda&& lambda) : m_db{ _db }
    {
        bRet = false;
        std::lock_guard lock(m_db.m_sync);

        try
        {
            beginTransaction();
            lambda();
            endTransaction();
            //commit();
            bRet = true;
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

} // namespace app::database
