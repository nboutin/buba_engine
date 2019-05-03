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

    r = sqlite3_prepare_v2(m_db,
                           "INSERT INTO Operation (date, description, amount) VALUES (?1, ?2, ?3);",
                           -1,
                           &m_stmt_insert_operation,
                           nullptr);

    if(r != SQLITE_OK)
    {
        cerr << sqlite3_errstr(r) << endl;
    }
}

Database_Project::~Database_Project()
{
    auto r = sqlite3_finalize(m_stmt_insert_operation);
    if(r != SQLITE_OK)
    {
        cerr << sqlite3_errstr(r) << endl;
    }

    r = sqlite3_close(m_db);
    if(r != SQLITE_OK)
    {
        cerr << sqlite3_errstr(r) << endl;
    }
}

bool Database_Project::insert_operation(const std::string& date,
                                        const std::string& description,
                                        double amount)
{
    auto r = sqlite3_reset(m_stmt_insert_operation);
    if(r != SQLITE_OK)
    {
        cerr << sqlite3_errstr(r) << endl;
        return false;
    }

    r = sqlite3_bind_text(m_stmt_insert_operation,
                          1,
                          date.c_str(),
                          -1,
                          reinterpret_cast<sqlite3_destructor_type>(-1));

    if(r != SQLITE_OK)
    {
        cerr << sqlite3_errstr(r) << endl;
        return false;
    }

    r = sqlite3_bind_text(m_stmt_insert_operation,
                          2,
                          description.c_str(),
                          -1,
                          reinterpret_cast<sqlite3_destructor_type>(-1));

    if(r != SQLITE_OK)
    {
        cerr << sqlite3_errstr(r) << endl;
        return false;
    }

    r = sqlite3_bind_double(m_stmt_insert_operation, 3, amount);
    if(r != SQLITE_OK)
    {
        cerr << sqlite3_errstr(r) << endl;
        return false;
    }

    r = sqlite3_step(m_stmt_insert_operation);

    if(r != SQLITE_DONE)
    {
        cerr << sqlite3_errstr(r) << endl;
        return false;
    }

    return false;
}

void Database_Project::create_table_operation()
{
    auto r = sqlite3_exec(m_db,
                          "CREATE TABLE Operation(date TEXT, description TEXT, amount REAL);",
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
    auto r = sqlite3_exec(
        m_db, "CREATE TABLE Category(name TEXT, description TEXT);", nullptr, nullptr, nullptr);

    if(r != SQLITE_OK)
    {
        cerr << sqlite3_errmsg(m_db) << endl;
        sqlite3_close(m_db);
        return;
    }
}

void Database_Project::create_table_label()
{
    auto r = sqlite3_exec(m_db, "CREATE TABLE Label(name TEXT);", nullptr, nullptr, nullptr);

    if(r != SQLITE_OK)
    {
        cerr << sqlite3_errmsg(m_db) << endl;
        sqlite3_close(m_db);
        return;
    }
}
