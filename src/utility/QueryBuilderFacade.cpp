#include "QueryBuilderFacade.h"

#include "QueryBuilder.h"

namespace app::utility
{

std::string QueryBuilderFacade::getSelectUsersWithLimOff(const int limit, const int offset)
{
    QueryBuilder query = QueryBuilder().select().from("User");

    if (limit > 0)
    {
        query.limit(limit);
    }

    if (offset > -1)
    {
        query.offset(offset);
    }

    return query.end().query();
}

} // namespace app::utility
