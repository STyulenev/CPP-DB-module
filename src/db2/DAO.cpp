#include "DAO.h"

#include <format>

namespace app::db2
{

UserDAO::UserDAO(sqlite3* db) : IDAO(db)
{

}

UserDAO::~UserDAO()
{

}

std::vector<UserDTO> UserDAO::selectAll()
{
    sqlite3_stmt* stmt = nullptr;

    sqlite3_prepare(_db, std::format("SELECT * FROM {};", UserDTO::tableName).c_str(), -1, &stmt, nullptr);
    sqlite3_step(stmt);

    std::vector<UserDTO> users;

    while (sqlite3_column_text(stmt, 0))
    {
        UserDTO user;
        user.id = std::stoi((char *)sqlite3_column_text(stmt, UserDTO::RowFields::ID));
        user.name = std::string((char *)sqlite3_column_text(stmt, UserDTO::RowFields::NAME));

        users.push_back(user);

        sqlite3_step( stmt );
    }

    sqlite3_finalize(stmt);

    return users;
}

bool UserDAO::insert(const DTOType && dto)
{
    char* messaggeError;

    const std::string query = std::format(
        "INSERT INTO {} VALUES (NULL, '{}');",
        UserDTO::tableName,
        dto.name
    );

    const int status = sqlite3_exec(_db, query.c_str(), nullptr, 0, &messaggeError);

    if (status != SQLITE_OK)
    {
        sqlite3_free(messaggeError);

        return false;
    }
    else
    {
        return true;
    }
}

} //namespace app::db2
