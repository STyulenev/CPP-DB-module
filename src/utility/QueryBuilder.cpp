#include "QueryBuilder.h"

#include <format>
#include <stdexcept>

namespace app::utility
{

const std::string& QueryBuilder::query() const
{
    return m_query;
}

QueryBuilder& QueryBuilder::select(const std::string& values)
{
    if (values.empty())
    {
        m_query += "SELECT * ";
    }
    else
    {
        m_query = m_query + std::format("SELECT {} ", values);
    }

    return *this;
}

QueryBuilder& QueryBuilder::from(const std::string &table)
{
    m_query = m_query + std::format("FROM {} ", table);
    return *this;
}

QueryBuilder& QueryBuilder::limit(const int limit)
{
    m_query = m_query + std::format("LIMIT {} ", limit);
    return *this;
}

QueryBuilder& QueryBuilder::offset(const int offset)
{
    m_query = m_query + std::format("OFFSET {} ", offset);
    return *this;
}

QueryBuilder& QueryBuilder::orderBy(const std::string &&column, const SortType type)
{
    m_query = m_query + std::format("ORDER BY {} {} ", column, getSortType(type));
    return *this;
}

QueryBuilder& QueryBuilder::comma_()
{
    m_query += ", ";
    return *this;
}

QueryBuilder& QueryBuilder::_and_()
{
    m_query += " AND ";
    return *this;
}

QueryBuilder& QueryBuilder::_or_()
{
    m_query += " OR ";
    return *this;
}

QueryBuilder& QueryBuilder::end()
{
    m_query += ";";
    return *this;
}

std::string QueryBuilder::getOperator(const Operator& op)
{
    switch (op)
    {
    case Operator::EQUAL:
        return "=";
    case Operator::GREATER:
        return ">";
    case Operator::GREATER_EQUAL:
        return ">=";
    case Operator::LESS:
        return "<";
    case Operator::LESS_EQUAL:
        return "<=";
    case Operator::NOT_EQUAL:
        return "!=";
    default:
        throw std::runtime_error("Unknown operator");
    }

    std::terminate();
}

std::string QueryBuilder::getSortType(const SortType& op)
{
    switch (op)
    {
    case SortType::ASC:
        return "ASC";
    case SortType::DESC:
        return "DESC";
    default:
        throw std::runtime_error("Unknown sort type");
    }

    std::terminate();
}

} // namespace app::utility
