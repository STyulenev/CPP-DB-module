#pragma once

#include "Query.h"

namespace app::db2
{

template<typename T>
class IDAO
{
protected:
    sqlite3* _db;

    IDAO() = delete;
    IDAO(sqlite3* db) : _db(db) {}

public:
    typedef T DTOType;

    virtual ~IDAO() = default;

    virtual std::vector<T> selectAll() = 0;
    virtual bool insert(const T &&) = 0;

};

class UserDAO final : public IDAO<UserDTO>
{   
public:
    UserDAO() = delete;
    explicit UserDAO(sqlite3* db);

    std::vector<DTOType> selectAll() override;
    bool insert(const DTOType &&) override;

};

} //namespace app::db2
