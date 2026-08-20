#include <iostream>

#include "db.h"
#include "transaction.h"

void db1Test()
{
    using namespace app::db1;

    Db db(DatabaseType::SQLITE);

    db.setDatabasePath("test.db");

    if (!db.generate())
    {
        throw std::runtime_error("");
    }

    {
        bool status{ false };
        std::lock_guard<std::recursive_mutex> lock(db.getLocker());
        Transaction(db, status, [&]() -> void
        {
            status = db.insert<UserTable>(
                UserEntry{
                    .name = "Mike"
                });

            if (!status)
            {
                throw std::runtime_error("");
            }

            auto users = db.selectAll<UserTable>();

            for (auto& user : users)
            {
                std::cout << user.id << " " << user.name << "\n";
            }
        });
    }
}

int main(int argc, char* argv[])
{
    db1Test();

    return 0;
}
