#include "tables.h"

namespace app::database
{

UserTable::UserTable()
{

}

std::string UserTable::getInsertQuery(const EntryType &entry)
{
    return std::format("INSERT INTO {} (name) VALUES ('{}');",
                       EntryType::tableName,
                       escapeQuote(entry.name)
    );
}

UserTable::EntryType UserTable::parse(const SQLiteQuery::Row &row) const
{
    if (EntryType::RowFields::FIELDS_COUNT > row.size())
    {
        throw std::runtime_error("");
    }

    EntryType r;

    r.id = from_char<decltype(r.id)>(row[EntryType::RowFields::ID]);
    r.name = std::string(row[EntryType::RowFields::NAME]);

    return r;
}

UserTable::Entries UserTable::parse(const SQLiteQuery &query) const
{
    UserTable::Entries _lh;

    for (SQLiteQuery::Rows curRow(const_cast<SQLiteQuery&>(query)); !!curRow; ++curRow)
    {
        UserEntry r = parse(*curRow);
        _lh.emplace_back(r);
    }

    return _lh;
}








} // namespace app::database
