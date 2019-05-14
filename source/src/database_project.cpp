//! \file	database_project.cpp
//! \date
//! \author
//! \copyright
//!
//! Software Component:

#include "database_project.h"

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"
#include "sqlite3.h"

using namespace buba;
using namespace std;

Database_Project::Database_Project(const std::string& pathname, db_connection_e connection)
{
    spdlog::info("{} {} {}", __func__, pathname, connection);

    auto r = sqlite3_open_v2(
        pathname.c_str(), &m_db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr);

    if(r != SQLITE_OK)
    {
        spdlog::error("{}", sqlite3_errmsg(m_db));
        sqlite3_close(m_db);
        return;
    }

    if(connection == db_connection_e::CREATE)
    {
        create_table_bank();
        create_table_account();
        create_table_category();
        create_table_label();
        create_table_transaction();
        populate_table_category();
    }

    use_foreign_keys();
    prepare_statements();
}

Database_Project::~Database_Project()
{
    spdlog::info("{}", __func__);

    auto r = sqlite3_finalize(m_stmt_insert_bank);
    if(r != SQLITE_OK)
    {
        spdlog::error("{}", sqlite3_errstr(r));
    }

    r = sqlite3_finalize(m_stmt_insert_account);
    if(r != SQLITE_OK)
    {
        spdlog::error("{}", sqlite3_errstr(r));
    }

    r = sqlite3_finalize(m_stmt_insert_transaction);
    if(r != SQLITE_OK)
    {
        spdlog::error("{}", sqlite3_errstr(r));
    }

    r = sqlite3_close(m_db);
    if(r != SQLITE_OK)
    {
        spdlog::error("{}", sqlite3_errstr(r));
    }
}

bool Database_Project::insert_bank(std::uint32_t id, const std::string& name)
{
    spdlog::info("{} {} {}", __func__, id, name);

    auto r = sqlite3_reset(m_stmt_insert_bank);
    if(r != SQLITE_OK)
    {
        spdlog::error("{}", sqlite3_errstr(r));
        return false;
    }

    // id
    r = sqlite3_bind_int(m_stmt_insert_bank, 1, id);
    if(r != SQLITE_OK)
    {
        spdlog::error("{}", sqlite3_errstr(r));
        return false;
    }

    // name
    r = sqlite3_bind_text(
        m_stmt_insert_bank, 2, name.c_str(), -1, reinterpret_cast<sqlite3_destructor_type>(-1));
    if(r != SQLITE_OK)
    {
        spdlog::error("{}", sqlite3_errstr(r));
        return false;
    }

    // Execute
    r = sqlite3_step(m_stmt_insert_bank);
    if(r != SQLITE_DONE)
    {
        spdlog::error("{}", sqlite3_errstr(r));
        return false;
        //    	if(r != SQLITE_CONSTRAINT)
        //        {
        //            cerr << sqlite3_errstr(r) << endl;
        //            return false;
        //        }
    }

    return true;
}

bool Database_Project::insert_account(const std::string& number,
                                      const std::string& name,
                                      std::uint32_t bank_id)
{
    spdlog::info("{} {} {} {}", __func__, number, name, bank_id);

    auto r = sqlite3_reset(m_stmt_insert_account);
    if(r != SQLITE_OK)
    {
        spdlog::error("{}", sqlite3_errstr(r));
        return false;
    }

    // number
    r = sqlite3_bind_text(m_stmt_insert_account,
                          1,
                          number.c_str(),
                          -1,
                          reinterpret_cast<sqlite3_destructor_type>(-1));
    if(r != SQLITE_OK)
    {
        spdlog::error("{}", sqlite3_errstr(r));
        return false;
    }

    // name
    r = sqlite3_bind_text(
        m_stmt_insert_account, 2, name.c_str(), -1, reinterpret_cast<sqlite3_destructor_type>(-1));
    if(r != SQLITE_OK)
    {
        spdlog::error("{}", sqlite3_errstr(r));
        return false;
    }

    // bank_id
    r = sqlite3_bind_int(m_stmt_insert_account, 3, bank_id);
    if(r != SQLITE_OK)
    {
        spdlog::error("{}", sqlite3_errstr(r));
        return false;
    }

    // Execute
    r = sqlite3_step(m_stmt_insert_account);
    if(r != SQLITE_DONE)
    {
        spdlog::error("{}", sqlite3_errstr(r));
        return false;
        //        if(r != SQLITE_CONSTRAINT)
        //        {
        //            cerr << sqlite3_errstr(r) << endl;
        //            return false;
        //        }
    }

    return true;
}

bool Database_Project::insert_transaction(const std::string& fitid,
                                          const std::string& date,
                                          const std::string& description,
                                          double amount,
                                          const std::string& account_number)
{
    spdlog::info("{} {} {} {} {} {}", __func__, fitid, date, description, amount, account_number);

    auto r = sqlite3_reset(m_stmt_insert_transaction);
    if(r != SQLITE_OK)
    {
        spdlog::error("{}", sqlite3_errstr(r));
        return false;
    }

    // FITID
    r = sqlite3_bind_text(m_stmt_insert_transaction,
                          1,
                          fitid.c_str(),
                          -1,
                          reinterpret_cast<sqlite3_destructor_type>(-1));
    if(r != SQLITE_OK)
    {
        spdlog::error("{}", sqlite3_errstr(r));
        return false;
    }

    // Date
    r = sqlite3_bind_text(m_stmt_insert_transaction,
                          2,
                          date.c_str(),
                          -1,
                          reinterpret_cast<sqlite3_destructor_type>(-1));
    if(r != SQLITE_OK)
    {
        spdlog::error("{}", sqlite3_errstr(r));
        return false;
    }

    // Description
    r = sqlite3_bind_text(m_stmt_insert_transaction,
                          3,
                          description.c_str(),
                          -1,
                          reinterpret_cast<sqlite3_destructor_type>(-1));
    if(r != SQLITE_OK)
    {
        spdlog::error("{}", sqlite3_errstr(r));
        return false;
    }

    // Amount
    r = sqlite3_bind_double(m_stmt_insert_transaction, 4, amount);
    if(r != SQLITE_OK)
    {
        spdlog::error("{}", sqlite3_errstr(r));
        return false;
    }

    // Account number
    r = sqlite3_bind_text(m_stmt_insert_transaction,
                          5,
                          account_number.c_str(),
                          -1,
                          reinterpret_cast<sqlite3_destructor_type>(-1));
    if(r != SQLITE_OK)
    {
        spdlog::error("{}", sqlite3_errstr(r));
        return false;
    }

    // Execute
    r = sqlite3_step(m_stmt_insert_transaction);
    if(r != SQLITE_DONE)
    {
        spdlog::error("{}", sqlite3_errstr(r));
        return false;
        //        if(r != SQLITE_CONSTRAINT)
        //        {
        //            cerr << sqlite3_errstr(r) << endl;
        //            return false;
        //        }
    }

    return true;
}

int get_banks_cb(void* context, int n_column, char** columns_data, char** columns_name)
{
    (void) n_column;
    (void) columns_name;

    if(context != nullptr)
    {
        // TODO Add check on columns_name
        vector<Bank_t>* banks = reinterpret_cast<vector<Bank_t>*>(context);

        int id = std::stoi(columns_data[0]);
        banks->push_back({id, columns_data[1]});
        return 0;
    }
    return 1;
}

std::vector<Bank_t> Database_Project::get_banks()
{
    spdlog::info("{}", __func__);

    vector<Bank_t> banks;

    auto r = sqlite3_exec(m_db, "SELECT * FROM Bank;", &get_banks_cb, &banks, nullptr);

    if(r != SQLITE_OK)
    {
        spdlog::error("{}", sqlite3_errstr(r));
        return {};
    }
    return banks;
}

int get_accounts_cb(void* context, int n_column, char** columns_data, char** columns_name)
{
    (void) n_column;
    (void) columns_name;

    if(context != nullptr)
    {
        // TODO Add check on columns_name
        vector<Account_t>* accounts = reinterpret_cast<vector<Account_t>*>(context);

        double balance = strtod(columns_data[2], nullptr);
        int bank_id    = std::stoi(columns_data[3]);
        accounts->push_back({columns_data[0], columns_data[1], balance, bank_id});
        return 0;
    }
    return 1;
}

std::vector<Account_t> Database_Project::get_accounts()
{
    spdlog::info("{}", __func__);

    vector<Account_t> accounts;

    auto r = sqlite3_exec(m_db, "SELECT * FROM Account;", &get_accounts_cb, &accounts, nullptr);
    if(r != SQLITE_OK)
    {
        spdlog::error("{}", sqlite3_errstr(r));
        return {};
    }
    return accounts;
}

int get_transactions_cb(void* context, int n_column, char** columns_data, char** columns_name)
{
    (void) n_column;
    (void) columns_name;

    if(context != nullptr)
    {
        // TODO Add check on columns_name
        vector<Transaction_t>* transactions = reinterpret_cast<vector<Transaction_t>*>(context);

        std::string fitid          = columns_data[0];
        std::string date           = columns_data[1];
        std::string description    = columns_data[2];
        double amount              = strtod(columns_data[3], nullptr);
        std::string account_number = columns_data[4];
        std::string label          = (columns_data[5] == nullptr) ? "" : columns_data[5];

        transactions->push_back({fitid, date, description, amount, account_number, label});
        return 0;
    }
    return 1;
}

std::vector<buba::Transaction_t> Database_Project::get_transactions()
{
    spdlog::info("{}", __func__);

    vector<Transaction_t> transactions;

    auto r = sqlite3_exec(
        m_db, "SELECT * FROM [Transaction];", &get_transactions_cb, &transactions, nullptr);
    if(r != SQLITE_OK)
    {
        spdlog::error("{}", sqlite3_errstr(r));
        return {};
    }

    return transactions;
}

std::vector<Transaction_t> Database_Project::get_transactions_without_label()
{
    spdlog::info("{}", __func__);

    vector<Transaction_t> transactions;

    auto r = sqlite3_exec(m_db,
                          "SELECT * FROM [Transaction] WHERE label_name IS NULL;",
                          &get_transactions_cb,
                          &transactions,
                          nullptr);
    if(r != SQLITE_OK)
    {
        spdlog::error("{}", sqlite3_errstr(r));
        return {};
    }

    return transactions;
}

int get_labels_cb(void* context, int n_column, char** columns_data, char** columns_name)
{
    (void) n_column;
    (void) columns_name;

    if(context != nullptr)
    {
        // TODO Add check on columns_name
        vector<Label_t>* labels = reinterpret_cast<vector<Label_t>*>(context);

        std::string name          = columns_data[0];
        std::string category_name = (columns_data[1] == nullptr) ? "" : columns_data[1];

        labels->push_back({name, category_name});
        return 0;
    }
    return 1;
}

std::vector<Label_t> Database_Project::get_labels()
{
    spdlog::info("{}", __func__);

    vector<Label_t> labels;

    auto r = sqlite3_exec(m_db, "SELECT * FROM Label;", &get_labels_cb, &labels, nullptr);
    if(r != SQLITE_OK)
    {
        spdlog::error("{}", sqlite3_errstr(r));
        return {};
    }

    return labels;
}

int get_categories_cb(void* context, int n_column, char** columns_data, char** columns_name)
{
    (void) n_column;
    (void) columns_name;

    if(context != nullptr)
    {
        // TODO Add check on columns_name
        vector<Category_t>* categories = reinterpret_cast<vector<Category_t>*>(context);

        std::string name = columns_data[0];

        categories->push_back({name});
        return 0;
    }
    return 1;
}

std::vector<Category_t> Database_Project::get_categories()
{
    spdlog::info("{}", __func__);

    vector<Category_t> categories;

    auto r =
        sqlite3_exec(m_db, "SELECT * FROM Category;", &get_categories_cb, &categories, nullptr);
    if(r != SQLITE_OK)
    {
        spdlog::error("{}", sqlite3_errstr(r));
        return {};
    }

    return categories;
}

bool Database_Project::set_bank_name(std::uint32_t id, const std::string& name)
{
    spdlog::info("{} {} {}", __func__, id, name);

    auto request = "UPDATE Bank SET name='" + name + "' WHERE id=" + std::to_string(id) + ";";

    auto r = sqlite3_exec(m_db, request.c_str(), nullptr, nullptr, nullptr);
    if(r != SQLITE_OK)
    {
        spdlog::error("{}", sqlite3_errstr(r));
        return false;
    }
    return true;
}

bool Database_Project::set_account_name(const std::string& number, const std::string& name)
{
    spdlog::info("{} {} {}", __func__, number, name);

    auto request = "UPDATE Account SET name='" + name + "' WHERE number=" + number + ";";

    auto r = sqlite3_exec(m_db, request.c_str(), nullptr, nullptr, nullptr);
    if(r != SQLITE_OK)
    {
        spdlog::error("{}", sqlite3_errstr(r));
        return false;
    }
    return true;
}

bool Database_Project::set_account_balance(const std::string& number, double balance)
{
    spdlog::info("{} {} {}", __func__, number, balance);

    auto request = "UPDATE Account SET balance="s + std::to_string(balance) + " WHERE number='"
                   + number + "';";

    auto r = sqlite3_exec(m_db, request.c_str(), nullptr, nullptr, nullptr);
    if(r != SQLITE_OK)
    {
        spdlog::error("{}", sqlite3_errstr(r));
        return false;
    }
    return true;
}

bool Database_Project::set_transaction_label(const std::string& fitid,
                                             const std::string& label_name)
{
    spdlog::info("{} {} {}", __func__, fitid, label_name);

    auto request =
        "UPDATE [Transaction] SET label_name='" + label_name + "' WHERE fitid='" + fitid + "';";

    auto r = sqlite3_exec(m_db, request.c_str(), nullptr, nullptr, nullptr);
    if(r != SQLITE_OK)
    {
        spdlog::error("{}", sqlite3_errstr(r));
        return false;
    }
    return true;
}

bool Database_Project::set_label_category(const std::string& label, const std::string& category)
{
    spdlog::info("{} {} {}", __func__, label, category);

    auto request = "UPDATE Label SET category_name='" + category + "' WHERE name='" + label + "';";

    auto r = sqlite3_exec(m_db, request.c_str(), nullptr, nullptr, nullptr);
    if(r != SQLITE_OK)
    {
        spdlog::error("{}", sqlite3_errstr(r));
        return false;
    }
    return true;
}

bool Database_Project::add_label(const std::string& name)
{
    spdlog::info("{} {}", __func__, name);

    auto request = "INSERT INTO	Label (name) VALUES ('" + name + "');";

    auto r = sqlite3_exec(m_db, request.c_str(), nullptr, nullptr, nullptr);
    if(r != SQLITE_OK)
    {
        spdlog::error("{}", sqlite3_errstr(r));
        return false;
    }
    return true;
}

void Database_Project::use_foreign_keys()
{
    spdlog::info("{}", __func__);

    auto r = sqlite3_exec(m_db, "PRAGMA foreign_keys = 1;", nullptr, nullptr, nullptr);
    if(r != SQLITE_OK)
    {
        spdlog::error("{}", sqlite3_errstr(r));
        sqlite3_close(m_db);
    }
}

void Database_Project::create_table_bank()
{
    spdlog::info("{}", __func__);

    auto r = sqlite3_exec(m_db,
                          "CREATE TABLE Bank ("
                          "id INTEGER NOT NULL, "
                          "name TEXT, "
                          "PRIMARY KEY(id)"
                          ");",
                          nullptr,
                          nullptr,
                          nullptr);

    if(r != SQLITE_OK)
    {
        spdlog::error("{}", sqlite3_errstr(r));
        sqlite3_close(m_db);
    }
}

void Database_Project::create_table_account()
{
    spdlog::info("{}", __func__);

    auto r = sqlite3_exec(m_db,
                          "CREATE TABLE Account ("
                          "number TEXT NOT NULL, "
                          "name TEXT , "
                          "balance REAL, "
                          "bank_id INTEGER NOT NULL, "
                          "PRIMARY KEY(number), "
                          "FOREIGN KEY(bank_id) REFERENCES Bank(id)"
                          ");",
                          nullptr,
                          nullptr,
                          nullptr);

    if(r != SQLITE_OK)
    {
        spdlog::error("{}", sqlite3_errstr(r));
        sqlite3_close(m_db);
    }
}

void Database_Project::create_table_transaction()
{
    spdlog::info("{}", __func__);

    auto r = sqlite3_exec(m_db,
                          "CREATE TABLE [Transaction] ("
                          "fitid          TEXT NOT NULL, "
                          "date           TEXT NOT NULL, "
                          "description    TEXT NOT NULL, "
                          "amount         REAL NOT NULL, "
                          "account_number TEXT NOT NULL REFERENCES Account (number), "
                          "label_name     TEXT REFERENCES Label (name), "
                          "PRIMARY KEY (fitid), "
                          "FOREIGN KEY (account_number) REFERENCES Account (number), "
                          "FOREIGN KEY (label_name) REFERENCES Label (name)"
                          ");",
                          nullptr,
                          nullptr,
                          nullptr);

    if(r != SQLITE_OK)
    {
        spdlog::error("{}", sqlite3_errstr(r));
        sqlite3_close(m_db);
    }
}

void Database_Project::create_table_category()
{
    spdlog::info("{}", __func__);

    auto r = sqlite3_exec(m_db,
                          "CREATE TABLE Category("
                          "name TEXT NOT NULL, "
                          "description TEXT, "
                          "PRIMARY KEY (name)"
                          ");",
                          nullptr,
                          nullptr,
                          nullptr);

    if(r != SQLITE_OK)
    {
        spdlog::error("{}", sqlite3_errstr(r));
        sqlite3_close(m_db);
    }
}

void Database_Project::populate_table_category()
{
    spdlog::info("{}", __func__);

    constexpr auto request = "INSERT INTO Category (name) VALUES('Essential');"
                             "INSERT INTO Category (name) VALUES('Security');"
                             "INSERT INTO Category (name) VALUES('Goals');"
                             "INSERT INTO Category (name) VALUES('Lifestyle');"
                             "INSERT INTO Category (name) VALUES('Optional');";

    auto r = sqlite3_exec(m_db, request, nullptr, nullptr, nullptr);

    if(r != SQLITE_OK)
    {
        spdlog::error("{}", sqlite3_errstr(r));
    }
}

void Database_Project::create_table_label()
{
    spdlog::info("{}", __func__);

    auto r = sqlite3_exec(m_db,
                          "CREATE TABLE Label("
                          "name TEXT NOT NULL, "
                          "category_name TEXT, "
                          "PRIMARY KEY(name), "
                          "FOREIGN KEY (category_name) REFERENCES Category(name)"
                          ");",
                          nullptr,
                          nullptr,
                          nullptr);

    if(r != SQLITE_OK)
    {
        spdlog::error("{}", sqlite3_errstr(r));
        sqlite3_close(m_db);
    }
}

void Database_Project::prepare_statements()
{
    spdlog::info("{}", __func__);

    // Bank
    auto r = sqlite3_prepare_v2(m_db,
                                "INSERT INTO Bank"
                                "(id, name)"
                                "VALUES(?1, ?2);",
                                -1,
                                &m_stmt_insert_bank,
                                nullptr);
    if(r != SQLITE_OK)
    {
        spdlog::error("{}", sqlite3_errstr(r));
    }

    // Account
    r = sqlite3_prepare_v2(m_db,
                           "INSERT INTO Account"
                           "(number, name, bank_id)"
                           "VALUES(?1, ?2, ?3);",
                           -1,
                           &m_stmt_insert_account,
                           nullptr);
    if(r != SQLITE_OK)
    {
        spdlog::error("{}", sqlite3_errstr(r));
    }

    // Transaction
    r = sqlite3_prepare_v2(m_db,
                           "INSERT INTO [Transaction] "
                           "(fitid, date, description, amount, account_number) "
                           "VALUES (?1, ?2, ?3, ?4, ?5);",
                           -1,
                           &m_stmt_insert_transaction,
                           nullptr);

    if(r != SQLITE_OK)
    {
        spdlog::error("{}", sqlite3_errstr(r));
    }
}
