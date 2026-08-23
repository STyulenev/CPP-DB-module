#include "Transaction.h"

#include "Query.h"
#include "DBConsts.h"

namespace app::db2
{

void Transaction::beginTransaction()
{
    Query(m_db._db, consts::SQLConsts::begin_transaction);
}

void Transaction::endTransaction()
{
    Query(m_db._db, consts::SQLConsts::end_transaction);
}

void Transaction::commit()
{
    Query(m_db._db, consts::SQLConsts::commit);
}

void Transaction::rollback()
{
    Query(m_db._db, consts::SQLConsts::rollback);
}

} // namespace app::db2
