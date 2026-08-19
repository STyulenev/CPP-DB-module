#pragma once

#include <cstring>
#include <string>
#include <vector>

#include <mutex>

#include "connection.h"

namespace app::db1
{

    struct SQLiteQuery
	{
        typedef std::vector<std::pair<std::string, bool>> SQLiteRow;
		struct Rows;

		struct Row
		{
			friend struct Rows;

            Row(const size_t& nColumn);

            bool operator!=(Row& other) const;
            const char* operator[](size_t i) const;
            bool operator!() const;
            size_t size() const;
            bool operator==(Row& other) const;

		protected:
            Row();

		protected:
            SQLiteRow m_row = {};
            size_t m_size = 0;
            bool m_stopFlag = false;

		};

		struct Rows
		{
            Rows(SQLiteQuery& owner);

            bool operator!() const;
            const Row& operator*() const;
            void operator++();

            void fillRow(SQLiteRow& row);

		protected:
			sqlite3_stmt* result = nullptr;
			Row current;

		};

        SQLiteQuery(SQLiteConnection& owner, std::string&& query);
        ~SQLiteQuery();

        bool operator !() const;

	protected:
		sqlite3* m_pDb;
		sqlite3_stmt* m_pRes;
		int fieldCount;
		std::scoped_lock<std::recursive_mutex> lock;

	};

} // namespace app::database
