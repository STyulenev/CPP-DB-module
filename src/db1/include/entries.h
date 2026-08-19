#pragma once

#include <string>

#include "db_constants.h"
#include "db_script.h"

namespace app::database
{

template<typename EntryT>
struct IEntry
{
    static std::string tableName;
    static std::string createTableScript;
};

struct UserEntry : public IEntry<UserEntry>
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

template<> inline std::string IEntry<UserEntry>::tableName = consts::TableNames::userTable;
template<> inline std::string IEntry<UserEntry>::createTableScript = scripts::user_table;

} // namespace app::database
