#pragma once

#include <memory>

#include "query.h"
#include "tables.h"

namespace app::database
{

template<typename T>
concept ValidDbTablesTypes = (
    std::is_final_v<T> &&
    requires (typename T::EntryType) { std::is_base_of_v<ITable<typename T::EntryType>, T>; } &&
    requires { typename T::EntryType; typename T::EntryType::RowFields; } &&
    requires(T t) { { t.getCreateTableScript() } -> std::same_as<std::string>; } &&
    requires(T t, const typename T::EntryType& entry) { { t.getInsertQuery(entry) } -> std::same_as<std::string>; }
);

enum class DatabaseType
{
    SQLITE,
    UNKNOWN
};

class Db final
{
public:
    friend class Transaction;

    Db() = delete;
    Db(const DatabaseType type);

    void setDatabasePath(const std::string& _db_path);
    std::string getDatabasePath() const;

    bool connect() noexcept;
    bool disconnect() noexcept;

    bool generate() noexcept;

    template<ValidDbTablesTypes T>
    constexpr T get() const
    {
        if constexpr (std::same_as<T, UserTable>) return m_user_table;
        // ...
        else
            throw std::runtime_error("");
    }

    template<ValidDbTablesTypes T>
    bool insert(const T::EntryType&& tableEntry) noexcept
    {
        try
        {
            std::lock_guard lock(m_sync);

            switch (m_type) {
            case DatabaseType::SQLITE:
            {
                if (SQLiteConnection* sqliteConn = dynamic_cast<SQLiteConnection*>(m_connection.get()))
                {
                    SQLiteQuery table(*sqliteConn, this->get<T>().getInsertQuery(tableEntry));
                }
                else
                {
                    throw std::runtime_error("");
                }
            }
            break;
            default:
                throw std::runtime_error("");
            }

            return true;
        }
        catch (...)
        {

        }

        return false;
    }

    template<ValidDbTablesTypes T, typename K = T::Entries>
    K selectAll() noexcept
    {
        try
        {
            std::lock_guard lock(m_sync);

            switch (m_type) {
            case DatabaseType::SQLITE:
            {
                if (SQLiteConnection* sqliteConn = dynamic_cast<SQLiteConnection*>(m_connection.get()))
                {
                    SQLiteQuery table(*sqliteConn, this->get<T>().selectAll());
                    K _rowVect = this->get<T>().parse(table);
                    return  _rowVect;
                }
                else
                {
                    throw std::runtime_error("");
                }
            }
            break;
            default:
                throw std::runtime_error("");
            }
        }
        catch (...)
        {

        }

        return  K();
    }

    std::recursive_mutex& getLocker();

private:
    std::recursive_mutex m_sync;
    std::shared_ptr<IConnection> m_connection;
    DatabaseType m_type;
    UserTable m_user_table;

};

} // namespace app::database
