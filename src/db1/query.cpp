#include "query.h"

#include <execution>

namespace app::db1
{

SQLiteQuery::Row::Row(const size_t &nColumn) :
    m_row(0),
    m_size(nColumn),
    m_stopFlag(false)
{
    if (nColumn > 0)
    {
        m_row.reserve(nColumn);
    }
}

bool SQLiteQuery::Row::operator!=(Row &other) const
{
    return !(*this == other);
}

const char* SQLiteQuery::Row::operator[](size_t i) const
{
    return m_row.at(i).first.c_str();
}

bool SQLiteQuery::Row::operator!() const
{
    return m_stopFlag;
}

size_t SQLiteQuery::Row::size() const
{
    return m_size;
}

bool SQLiteQuery::Row::operator==(Row &other) const
{
    if (other.m_stopFlag)
        return m_stopFlag;

    if (m_size != other.m_size)
        return false;

    for (size_t i = 0; i < m_size; ++i)
        if (!!strcmp(m_row[i].first.c_str(), other.m_row[i].first.c_str()))
            return false;

    return true;
}

SQLiteQuery::Row::Row() :
    m_row(0),
    m_size(0),
    m_stopFlag(false)
{

}

SQLiteQuery::Rows::Rows(SQLiteQuery &owner) :
    result(owner.m_pRes),
    current(owner.fieldCount)
{
    if (!result)
    {
        current.m_stopFlag = true;
        return;
    }

    sqlite3_reset(owner.m_pRes);
    int rc = sqlite3_step(result);
    current.m_size = owner.fieldCount;

    if (rc == SQLITE_ROW)
    {
        fillRow(current.m_row);
    }
    else if (rc == SQLITE_DONE)
    {
        current.m_stopFlag = true;
    }
}

bool SQLiteQuery::Rows::operator!() const
{
    return !current;
}

const SQLiteQuery::Row &SQLiteQuery::Rows::operator*() const
{
    return current;
}

void SQLiteQuery::Rows::operator++()
{
    const int rc = sqlite3_step(result);

    if (SQLITE_ROW == rc)
    {
        fillRow(current.m_row);
    }
    else if (SQLITE_DONE == rc)
    {
        current.m_stopFlag = true;
    }
}

void SQLiteQuery::Rows::fillRow(SQLiteRow &row)
{
    row.clear();
    for (auto filedCt = 0; filedCt < current.m_size; filedCt++)
    {
        std::string str;
        auto type = sqlite3_column_type(result, filedCt);
        auto data = sqlite3_column_text(result, filedCt);

        if (data != NULL)
        {
            str = ((char*)(const_cast<unsigned char*>(data)));
        }
        else
        {
            str = "NULL";
        }

        row.push_back(std::make_pair(str, (type == 5 ? true : false)));
    }
}

SQLiteQuery::SQLiteQuery(SQLiteConnection& owner, std::string&& query) :
    m_pDb(owner.pDb),
    m_pRes(0),
    fieldCount(0),
    lock(owner.sync)
{
    if (NULL == m_pDb)
    {
        return;
    }

    if (!owner.exec(std::forward<std::string>(query), &m_pRes))
    {
        throw std::runtime_error("");
    }

    int rc = sqlite3_step(m_pRes);

    if (rc != SQLITE_DONE && rc != SQLITE_ROW)
    {
        throw std::runtime_error("");
    }

    fieldCount = sqlite3_column_count(m_pRes);
}

SQLiteQuery::~SQLiteQuery()
{
    try
    {
        if (!m_pRes)
        {
            return;
        }

        if (m_pRes)
        {
            int rc = 0;

            if ((rc = sqlite3_finalize(m_pRes)) != SQLITE_OK)
            {
                // ...
            }

            m_pRes = nullptr;
        }
    }
    catch (...)
    {

    }
}

bool SQLiteQuery::operator !() const
{
    return m_pRes != 0;
}

} // namespace app::database
