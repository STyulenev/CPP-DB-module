#include <iostream>

#include "QueryBuilder.h"
#include "QueryBuilderFacade.h"

int main(int argc, char* argv[])
{
    using namespace app::utility;

    std::cout << QueryBuilder()
                     .select()
                     .from("User")
                     .limit(2)
                     .offset(3)
                     .end()
                     .query() << std::endl;

    std::cout << QueryBuilderFacade::getSelectUsersWithLimOff(10, 0) << std::endl;

    return 0;
}
