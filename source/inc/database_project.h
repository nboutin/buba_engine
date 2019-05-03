//! \file	database_project.h
//! \date
//! \author
//! \copyright
//!
//! Software Component:

#pragma once

#include <sqlite3.h>

#include <string>

namespace buba
{
class Database_Project
{
public:
    Database_Project(const std::string& pathname);
    ~Database_Project();

    bool
    insert_operation(const std::string& date, const std::string& description, double amount);

private:
    void create_table_operation();
    void create_table_category();
    void create_table_label();

    sqlite3* m_db                         = nullptr;
    sqlite3_stmt* m_stmt_insert_operation = nullptr;
};
}
