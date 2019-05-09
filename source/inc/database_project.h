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
enum class db_connection_e { OPEN, CREATE };

class Database_Project
{
public:
    Database_Project(const std::string& pathname,
                     db_connection_e connection = db_connection_e::CREATE);
    ~Database_Project();

    bool insert_bank(std::uint32_t id, const std::string& name);

    bool insert_account(const std::string& number, const std::string& name, std::uint32_t bank_id);

    bool insert_transaction(const std::string& fitid,
                            const std::string& date,
                            const std::string& description,
                            double amount,
                            const std::string& account_number);

    // TODO return a map ?
    std::vector<Transaction_t> get_transactions_all();

private:
    void create_table_transaction();
    void create_table_category();
    void create_table_label();
    void create_table_bank();
    void create_table_account();

    void prepare_statements();

    static int get_transactions_all_cb(void*, int, char**, char**);

    sqlite3* m_db                           = nullptr;
    sqlite3_stmt* m_stmt_insert_bank        = nullptr;
    sqlite3_stmt* m_stmt_insert_account     = nullptr;
    sqlite3_stmt* m_stmt_insert_transaction = nullptr;
};
}
