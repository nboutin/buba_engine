//! \file	database_project.cpp
//! \date
//! \author
//! \copyright
//!
//! Software Component:

#include "database_project.h"

#include <sqlite3.h>

#include <iostream>

using namespace buba;
using namespace std;

Database_Project::Database_Project(const std::string& pathname)
{
    auto r = sqlite3_open_v2(
        pathname.c_str(), &m_db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr);

    if(r != SQLITE_OK)
    {
        cerr << sqlite3_errmsg(m_db) << endl;
        sqlite3_close(m_db);
        return;
    }

    create_table_operation();
    create_table_category();
    create_table_label();
}

void Database_Project::create_table_operation()
{
    auto r =
        sqlite3_exec(m_db,
                     "CREATE TABLE Operation(date TEXT, description TEXT, debit_credit INTEGER);",
                     nullptr,
                     nullptr,
                     nullptr);

    if(r != SQLITE_OK)
    {
        cerr << sqlite3_errmsg(m_db) << endl;
        sqlite3_close(m_db);
        return;
    }
}

void Database_Project::create_table_category()
{
    auto r =
        sqlite3_exec(m_db,
                     "CREATE TABLE Category(name TEXT, description TEXT);",
                     nullptr,
                     nullptr,
                     nullptr);

    if(r != SQLITE_OK)
    {
        cerr << sqlite3_errmsg(m_db) << endl;
        sqlite3_close(m_db);
        return;
    }
}

void Database_Project::create_table_label()
{
    auto r =
        sqlite3_exec(m_db,
                     "CREATE TABLE Label(name TEXT);",
                     nullptr,
                     nullptr,
                     nullptr);

    if(r != SQLITE_OK)
    {
        cerr << sqlite3_errmsg(m_db) << endl;
        sqlite3_close(m_db);
        return;
    }
}
