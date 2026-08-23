#include <iostream>

#include "Database.h"
#include "Transaction.h"

void db2Test()
{
    using namespace app::db2;

    std::shared_ptr<IDB> db = std::make_shared<SQLiteDB>();

    if (db->open() && db->generateDB())
    {
        bool status{ false };

        Transaction(db, status, [&]() -> void
        {
            auto dao = getDAO<UserDTO>(db);

            bool status = dao->insert(
                UserDTO{
                    .name = "Mike"
                });

            if (!status)
            {
                throw std::runtime_error("");
            }

            auto users = dao->selectAll();

            for (auto& user : users)
            {
                std::cout << user.id << " " << user.name << "\n";
            }
        });
    }
}

int main(int argc, char* argv[])
{
    db2Test();

    return 0;
}
