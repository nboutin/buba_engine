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

Database_Project::Database_Project(const std::string& pathname, db_connection_e connection)
{
    auto r = sqlite3_open_v2(
        pathname.c_str(), &m_db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr);

    if(r != SQLITE_OK)
    {
        cerr << sqlite3_errmsg(m_db) << endl;
        sqlite3_close(m_db);
        return;
    }

    if(connection == db_connection_e::CREATE)
    {
        create_table_transaction();
        create_table_category();
        create_table_label();
        create_table_bank();
        create_table_account();
    }

    r = sqlite3_prepare_v2(m_db,
                           "INSERT INTO [Transaction] "
                           "(date, description, amount) "
                           "VALUES (?1, ?2, ?3);",
                           -1,
                           &m_stmt_insert_transaction,
                           nullptr);

    if(r != SQLITE_OK)
    {
        cerr << __func__ << ":" << sqlite3_errmsg(m_db) << endl;
    }
}

Database_Project::~Database_Project()
{
    auto r = sqlite3_finalize(m_stmt_insert_transaction);
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

bool Database_Project::insert_transaction(const std::string& date,
                                          const std::string& description,
                                          double amount)
{
    auto r = sqlite3_reset(m_stmt_insert_transaction);
    if(r != SQLITE_OK)
    {
        cerr << sqlite3_errstr(r) << endl;
        return false;
    }

    r = sqlite3_bind_text(m_stmt_insert_transaction,
                          1,
                          date.c_str(),
                          -1,
                          reinterpret_cast<sqlite3_destructor_type>(-1));

    if(r != SQLITE_OK)
    {
        cerr << sqlite3_errstr(r) << endl;
        return false;
    }

    r = sqlite3_bind_text(m_stmt_insert_transaction,
                          2,
                          description.c_str(),
                          -1,
                          reinterpret_cast<sqlite3_destructor_type>(-1));

    if(r != SQLITE_OK)
    {
        cerr << sqlite3_errstr(r) << endl;
        return false;
    }

    r = sqlite3_bind_double(m_stmt_insert_transaction, 3, amount);
    if(r != SQLITE_OK)
    {
        cerr << sqlite3_errstr(r) << endl;
        return false;
    }

    r = sqlite3_step(m_stmt_insert_transaction);

    if(r != SQLITE_DONE)
    {
        cerr << sqlite3_errstr(r) << endl;
        return false;
    }

    return false;
}

int Database_Project::get_transactions_all_cb(void* context,
                                              int n_column,
                                              char** columns_data,
                                              char** columns_name)
{
    (void) n_column;
    (void) columns_name;

    if(context != nullptr)
    {
        vector<Transaction_t>* operations = reinterpret_cast<vector<Transaction_t>*>(context);
        operations->push_back({columns_data[0], columns_data[1], strtod(columns_data[2], nullptr)});
        return 0;
    }
    return 1;
}

std::vector<buba::Transaction_t> Database_Project::get_transactions_all()
{
    vector<Transaction_t> transaction;

    auto r = sqlite3_exec(m_db,
                          "SELECT * FROM [Transaction];",
                          &Database_Project::get_transactions_all_cb,
                          &transaction,
                          nullptr);
    if(r != SQLITE_OK)
    {
        cerr << sqlite3_errstr(r) << endl;
        return {};
    }

    return transaction;
}

void Database_Project::create_table_transaction()
{
    auto r = sqlite3_exec(m_db,
                          "CREATE TABLE [Transaction]("
                          "date TEXT, "
                          "description TEXT, "
                          "amount REAL, "
                          "account_number INTEGER, "
                          "category_name TEXT, "
                          //"PRIMARY KEY(), "
                          "FOREIGN KEY (account_number) REFERENCES Account(number), "
                          "FOREIGN KEY (category_name) REFERENCES Category(name)"
                          ");",
                          nullptr,
                          nullptr,
                          nullptr);

    if(r != SQLITE_OK)
    {
        cerr << __func__ << ":" << sqlite3_errmsg(m_db) << endl;
        sqlite3_close(m_db);
    }
}

void Database_Project::create_table_category()
{
    auto r = sqlite3_exec(m_db,
                          "CREATE TABLE Category("
                          "name TEXT NOT NULL, "
                          "PRIMARY KEY (name)"
                          ");",
                          nullptr,
                          nullptr,
                          nullptr);

    if(r != SQLITE_OK)
    {
        cerr << __func__ << ":" << sqlite3_errmsg(m_db) << endl;
        sqlite3_close(m_db);
    }
}

void Database_Project::create_table_label()
{
    auto r = sqlite3_exec(m_db,
                          "CREATE TABLE Label("
                          "name TEXT NOT NULL, "
                          "category_id INTEGER NOT NULL, "
                          "PRIMARY KEY(name), "
                          "FOREIGN KEY (category_id) REFERENCES Category(name)"
                          ");",
                          nullptr,
                          nullptr,
                          nullptr);

    if(r != SQLITE_OK)
    {
        cerr << sqlite3_errmsg(m_db) << endl;
        sqlite3_close(m_db);
    }
}

void Database_Project::create_table_bank()
{
    auto r = sqlite3_exec(m_db,
                          "CREATE TABLE Bank ("
                          "name TEXT NOT NULL, "
                          "PRIMARY KEY(name)"
                          ");",
                          nullptr,
                          nullptr,
                          nullptr);

    if(r != SQLITE_OK)
    {
        cerr << __func__ << ":" << sqlite3_errmsg(m_db) << endl;
        sqlite3_close(m_db);
    }
}

void Database_Project::create_table_account()
{
    auto r = sqlite3_exec(m_db,
                          "CREATE TABLE Account ("
                          "number INTEGER NOT NULL, "
                          "name TEXT, "
                          "bank_name TEXT, "
                          "PRIMARY KEY(number), "
                          "FOREIGN KEY(bank_name) REFERENCES Bank(name)"
                          ");",
                          nullptr,
                          nullptr,
                          nullptr);

    if(r != SQLITE_OK)
    {
        cerr << __func__ << ":" << sqlite3_errmsg(m_db) << endl;
        sqlite3_close(m_db);
    }
}
