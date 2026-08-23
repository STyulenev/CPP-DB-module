#pragma once

namespace app::db2::consts
{

    struct TableNames
    {
        static constexpr auto userTable = "User";
    };

    struct SQLConsts
    {
        static constexpr auto begin_transaction = "BEGIN TRANSACTION;";
        static constexpr auto commit = "COMMIT;";
        static constexpr auto end_transaction = "END TRANSACTION;";
        static constexpr auto rollback = "ROLLBACK;";
    };

} // namespace app::db2::consts

namespace app::db2::scripts
{

    static constexpr char user_table[] =
    {
        "CREATE TABLE IF NOT EXISTS User "
        "("
        "    id INTEGER, "
        "    name TEXT NOT NULL, "
        "    PRIMARY KEY(id AUTOINCREMENT)"
        ");"
    };

} // namespace app::db2::scripts

