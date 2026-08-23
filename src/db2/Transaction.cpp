#include "Transaction.h"

#include "Query.h"
#include "DBConsts.h"

namespace app::db2
{

void Transaction::beginTransaction()
{
    getQuery(m_db, consts::SQLConsts::begin_transaction);
}

void Transaction::endTransaction()
{
    getQuery(m_db, consts::SQLConsts::end_transaction);
}

void Transaction::commit()
{
    getQuery(m_db, consts::SQLConsts::commit);
}

void Transaction::rollback()
{
    getQuery(m_db, consts::SQLConsts::rollback);
}

} // namespace app::db2
