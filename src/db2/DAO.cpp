#include "DAO.h"

#include <format>

#include <sqlite3.h>
#include <string>
#include <vector>

namespace app::db2
{

UserDAO::UserDAO(sqlite3* db) :
    IDAO(db)
{

}

std::vector<UserDTO> UserDAO::selectAll()
{
    std::vector<UserDTO> users;

    try
    {
        const std::string queryStr = std::format("SELECT * FROM {};", UserDTO::tableName);
        Query(_db, queryStr).parse(users);
    }
    catch (...)
    {

    }

    return users;
}

bool UserDAO::insert(const DTOType&& dto)
{
    const std::string query = std::format(
        "INSERT INTO {} VALUES (NULL, '{}');",
        UserDTO::tableName,
        dto.name
    );

    try
    {
        Query(_db, query);
    }
    catch (...)
    {
        return false;
    }

    return true;
}

} //namespace app::db2
