#include "Transaction.h"

#include "Query.h"
#include "DBConsts.h"

namespace app::db2
{

Transaction::Transaction(std::shared_ptr<IDB> &_db) :
    m_db{ _db },
    m_error{ false }
{
    std::shared_ptr<IQuery> query = getQuery(m_db, consts::SQLConsts::begin_transaction);
    query->exec();
}

Transaction::~Transaction()
{
    try
    {
        std::shared_ptr<IQuery> query = getQuery(m_db, consts::SQLConsts::end_transaction);
        query->exec();
    }
    catch (...)
    {
        std::terminate();
    }
}

Transaction& Transaction::transaction(const std::function<void ()>& func)
{
    if (!m_error)
    {
        try
        {
            func();

            std::shared_ptr<IQuery> query = getQuery(m_db, consts::SQLConsts::commit);
            query->exec();
        }
        catch (...)
        {

            m_error = true;
        }
    }

    return *this;
}

Transaction& Transaction::error(const std::function<void ()>& func) noexcept
{
    if (m_error)
    {
        func();

        try
        {
            std::shared_ptr<IQuery> query = getQuery(m_db, consts::SQLConsts::rollback);
            query->exec();

            m_error = false;
        }
        catch (...)
        {

        }
    }

    return *this;
}

} // namespace app::db2
