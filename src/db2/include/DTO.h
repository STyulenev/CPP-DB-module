#pragma once

#include <string>

#include "DBConsts.h"

namespace app::db2
{

template<typename T>
struct IDTO
{
    static std::string tableName;
    static std::string createTableScript;
};

struct UserDTO final : public IDTO<UserDTO>
{
    int         id;
    std::string name;

    enum RowFields
    {
        ID,
        NAME,

        FIELDS_COUNT
    };
};

template<> inline std::string IDTO<UserDTO>::tableName = consts::TableNames::userTable;
template<> inline std::string IDTO<UserDTO>::createTableScript = scripts::user_table;

} // namespace app::db2
