#pragma once

#include "Query.h"

namespace app::db2
{

class IDB;

template<typename T>
class IDAO
{
protected:
    std::shared_ptr<IDB> _db;

    IDAO() = delete;
    IDAO(const std::shared_ptr<IDB>& db) : _db(db) {}

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
    explicit UserDAO(const std::shared_ptr<IDB>& db);

    std::vector<DTOType> selectAll() override;
    bool insert(const DTOType &&) override;

};

} //namespace app::db2
