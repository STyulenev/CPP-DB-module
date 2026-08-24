#pragma once

#include <string>

namespace app::utility
{

class QueryBuilderFacade
{
private:
    QueryBuilderFacade() {}
    ~QueryBuilderFacade() {}

public:
    static std::string getSelectUsersWithLimOff(const int limit = -1, const int offset = -1);

};

} // namespace app::utility
