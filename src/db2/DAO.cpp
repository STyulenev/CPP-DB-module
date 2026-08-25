#include "DAO.h"

#include <format>

#include <sqlite3.h>
#include <string>
#include <vector>

namespace app::db2
{

UserDAO::UserDAO(const std::shared_ptr<IDB>& db) :
    IDAO(db)
{

}

std::vector<UserDTO> UserDAO::selectAll() noexcept
{
    std::vector<UserDTO> users;

    try
    {
        const std::string queryStr = std::format("SELECT * FROM {};", DTOType::tableName);
        std::shared_ptr<IQuery> query = getQuery(_db, queryStr);
        query->prepare();
        query->parse(users);
    }
    catch (...)
    {

    }

    return users;
}

bool UserDAO::insert(const DTOType&& dto) noexcept
{
    const std::string queryStr = std::format(
        "INSERT INTO {} VALUES (NULL, '{}');",
        DTOType::tableName,
        dto.name
    );

    try
    {
        std::shared_ptr<IQuery> query = getQuery(_db, queryStr);
        //query->prepare();
        query->exec();
    }
    catch (...)
    {
        return false;
    }

    return true;
}

} //namespace app::db2
