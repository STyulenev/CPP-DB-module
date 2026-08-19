#pragma once

namespace app::db1::consts
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

} // namespace app::db1::consts
