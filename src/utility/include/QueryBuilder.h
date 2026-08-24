#pragma once

#include <string>

namespace app::utility
{

class QueryBuilder
{
public:
    enum class Operator
    {
        EQUAL,         // =
        GREATER,       // >
        GREATER_EQUAL, // >=
        LESS,          // <
        LESS_EQUAL,    // <=
        NOT_EQUAL      // !=
    };

    enum class SortType
    {
        ASC,
        DESC
    };

    const std::string& query() const;

    QueryBuilder& select(const std::string& values = std::string());

    QueryBuilder& from(const std::string& table);

    QueryBuilder& limit(const int limit);

    QueryBuilder& offset(const int offset);

    QueryBuilder& orderBy(const std::string&& column, const SortType type = SortType::ASC);

    QueryBuilder& comma_();
    QueryBuilder& _and_();
    QueryBuilder& _or_();
    QueryBuilder& end();

private:
    std::string getOperator(const Operator& op);
    std::string getSortType(const SortType& op);

private:
    std::string m_query;
    bool m_where = false;

};

} // namespace app::utility
