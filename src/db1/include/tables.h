#pragma once

#include <format>

#include "entries.h"
#include "query.h"

// Функция для перевода char в численные переменные
template <typename T>
inline T from_char(std::string str)
{
    if (str == "NULL")
    {
        return -1;
    }

    T result{};
    auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), result);

    if (ec == std::errc())
        return result;
    else if (ec == std::errc::invalid_argument)
        throw  std::runtime_error(std::format("error when convertation from string {}", str));
    else if (ec == std::errc::result_out_of_range)
        throw std::runtime_error(std::format("error when convertation from string {} : result out of range", str));

    return {};
}

// Функция замены ' на ''
inline std::string escapeQuote(std::span<const char> _szSource)
{
    if (_szSource.size() == 0)
        return std::string();

    std::string source(_szSource.data());
    size_t pos = 0;

    while (std::string::npos != (pos = source.find("'", pos)))
    {
        source.replace(pos, 1, "\'\'", 2);
        pos += 2;
    }

    return source;
}

namespace app::db1
{

template<typename EntryT>
class ITable
{
public:
    std::string _tableName;

public:
    typedef EntryT EntryType;
    typedef std::vector<UserEntry> Entries;

    ITable() = default;
    virtual ~ITable() {}

    std::string selectAll() const
    {
        return std::format("SELECT * FROM {};", EntryType::tableName);
    }

    std::string getCreateTableScript() const
    {
        return EntryType::createTableScript;
    }

    virtual std::string getInsertQuery(const EntryType& entry) = 0;
    virtual EntryType   parse(const SQLiteQuery::Row& row) const = 0;
    virtual Entries     parse(const SQLiteQuery& query)    const = 0;

};

class UserTable final : public ITable<UserEntry>
{
public:
    UserTable();

    virtual std::string getInsertQuery(const EntryType& entry) override;

    virtual EntryType parse(const SQLiteQuery::Row& row) const override;
    virtual UserTable::Entries parse(const SQLiteQuery& query) const override;

};

} // namespace app::database
