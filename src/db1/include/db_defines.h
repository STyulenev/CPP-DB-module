#pragma once

#ifndef CREATE_TABLE
#define CREATE_TABLE(table_name, entity_name) \
class table_name final : public ITable<entity_name> \
{ \
public: \
    virtual std::string getInsertQuery(const EntryType& entry) override; \
    virtual EntryType parse(const SQLiteQuery::Row& row) const override; \
    virtual table_name::Entries parse(const SQLiteQuery& query) const override; \
};
#endif
