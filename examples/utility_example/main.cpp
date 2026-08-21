#include <iostream>

#include "QueryBuilder.h"

int main(int argc, char* argv[])
{
    using namespace app::utility;

    std::cout << QueryBuilder()
                     .select().spase()
                     .from("User").spase()
                     .limit(2).spase()
                     .offset(3)
                     .end()
                     .query() << std::endl;

    return 0;
}
