#include "db.h"
#include "transaction.h"

namespace app::db1
{

    Db::Db(const DatabaseType type) :
        m_type(type)
    {
        switch (m_type) {
        case DatabaseType::SQLITE:
            m_connection = std::make_shared<SQLiteConnection>();
            break;
        default:
            break;
        }
    }

    void Db::setDatabasePath(const std::string& _db_path)
	{
        m_connection->setPath(_db_path);
	}

    std::string Db::getDatabasePath() const
	{
        return m_connection->getPath();
	}

	bool Db::connect() noexcept
	{
        return m_connection->tryConnect();
	}

	bool Db::disconnect() noexcept
	{
        return m_connection->disconnect();
	}

    bool Db::generate() noexcept
	{
        try
		{
			if (!connect())
			{
                throw std::runtime_error("");
			}

		    bool bRet{ false };
            std::lock_guard lock(m_sync);
		    Transaction(*this, bRet, [&]()
		    {
				// Tables:
                switch (m_type) {
                case DatabaseType::SQLITE:
                {
                    if (SQLiteConnection* sqliteConn = dynamic_cast<SQLiteConnection*>(m_connection.get()))
                    {
                        SQLiteQuery user_tbl(*sqliteConn, m_user_table.getCreateTableScript());
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
		    });

		    return bRet;
		}
        catch (...)
        {

        }

		return false;
	}

    std::recursive_mutex& Db::getLocker()
    {
        return m_sync;
    }

} // namespace app::db1
