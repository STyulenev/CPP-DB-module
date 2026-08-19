#pragma once

namespace app::database::scripts
{

    static constexpr char user_table[] =
	{
        "CREATE TABLE IF NOT EXISTS User "
        "("
        "    id INTEGER, "
        "    name TEXT NOT NULL, "
        "    PRIMARY KEY(id AUTOINCREMENT)"
        ");"
	};

} // namespace app::database::scripts
