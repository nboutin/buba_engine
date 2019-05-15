//! \file	database_project.h
//! \date
//! \author
//! \copyright
//!
//! Software Component:

#pragma once

#include "buba.h"

#include "spdlog/fmt/ostr.h"
#include "sqlite3.h"

#include <string>
#include <vector>

namespace buba
{
enum class db_connection_e { OPEN, CREATE };

template<typename OStream>
OStream& operator<<(OStream& os, const db_connection_e& c)
{
    switch(c)
    {
    case db_connection_e::OPEN: return os << "open";
    case db_connection_e::CREATE: return os << "create";
    }
    return os;
}

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

    std::vector<Bank_t> get_banks();
    std::vector<Account_t> get_accounts();
    std::vector<Transaction_t> get_transactions();    // TODO return a map ?
    std::vector<Transaction_t> get_transactions_without_label();
    std::vector<Label_t> get_labels();
    std::vector<Category_t> get_categories();

    bool set_bank_name(std::uint32_t id, const std::string& name);
    bool set_account_name(const std::string& number, const std::string& name);
    bool set_account_balance(const std::string& number, double balance);
    bool set_transaction_label(const std::string& fitid, const std::string& label_name);
    bool set_label_category(const std::string& label, const std::string& category);

    bool add_label(const std::string& name);

private:
    void use_foreign_keys();
    void create_table_transaction();
    void create_table_category();
    void create_table_label();
    void create_table_bank();
    void create_table_account();

    void populate_table_category();
    void prepare_statements();

    sqlite3* m_db                              = nullptr;
    sqlite3_stmt* m_stmt_insert_bank           = nullptr;
    sqlite3_stmt* m_stmt_insert_account        = nullptr;
    sqlite3_stmt* m_stmt_insert_transaction    = nullptr;
    sqlite3_stmt* m_stmt_set_transaction_label = nullptr;
};
}
