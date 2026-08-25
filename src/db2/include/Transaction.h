#pragma once

#include "Database.h"

#include <functional>

namespace app::db2
{

class Transaction final
{
public:
    Transaction() = delete;
    explicit Transaction(std::shared_ptr<IDB>& db);
    ~Transaction();

    Transaction(const Transaction&) = delete;
    Transaction& operator=(const Transaction&) = delete;
    Transaction(Transaction&&) = delete;
    Transaction& operator=(Transaction&&) = delete;

    Transaction& transaction(const std::function<void()>& func);
    Transaction& error(const std::function<void()>& func) noexcept;

private:
    void* operator new(std::size_t)   = delete;
    void* operator new[](std::size_t) = delete;

private:
    std::shared_ptr<IDB> m_db;
    bool                 m_error;

};

} // namespace app::db2
