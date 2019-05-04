//! \file	database_project.h
//! \date
//! \author
//! \copyright
//!
//! Software Component:

#pragma once

#include "buba.h"

#include <sqlite3.h>

#include <string>
#include <vector>

namespace buba
{
class Database_Project
{
public:
    Database_Project(const std::string& pathname);
    ~Database_Project();

    bool insert_operation(const std::string& date, const std::string& description, double amount);

    // TODO return a map ?
    std::vector<Operation_t> get_operations_all();

private:
    void create_table_operation();
    void create_table_category();
    void create_table_label();
    void create_table_bank();
    void create_table_account();

    static int get_operations_all_cb(void*, int, char**, char**);

    sqlite3* m_db                         = nullptr;
    sqlite3_stmt* m_stmt_insert_operation = nullptr;
};
}
