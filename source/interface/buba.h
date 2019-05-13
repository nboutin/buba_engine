//! \file buba.h
//! \date 29/04/2019
//! \author nboutin
//! \copyright
//!
//! Software Component: BuBa_engine

#pragma once

#include <memory>
#include <string>
#include <vector>

namespace buba
{
class Database_Project;

struct Bank_t
{
    int id;
    std::string name;
};

struct Account_t
{
    std::string number;
    std::string name;
    double balance;
    int bank_id;
};

struct Transaction_t
{
    std::string fitid;
    std::string date;
    std::string description;
    double amount;
    std::string account_number;
    std::string label;
};

struct Label_t
{
    std::string name;
    std::string category_name;
};

struct Category_t
{
    std::string name;
};

class Budget_Battle
{
public:
    Budget_Battle();
    ~Budget_Battle();

    bool project_create(const std::string& pathname);
    bool project_open(const std::string& pathname);
    void project_close();

    bool import_ofx(const std::string& pathname);

    std::vector<Bank_t> get_banks() const;
    std::vector<Account_t> get_accounts() const;
    std::vector<Transaction_t> get_transactions() const;
    std::vector<Transaction_t> get_transactions_without_label() const;
    std::vector<Label_t> get_labels() const;
    std::vector<Category_t> get_categories() const;

    bool set_bank_name(std::uint32_t bank_id, const std::string& name);
    bool set_account_name(const std::string& number, const std::string& name);
    bool set_transaction_label(const std::string fitid, const std::string& label_name);
    bool set_label_category(const std::string& label, const std::string& category);

    bool add_label(const std::string& name);

private:
    void configure_loggers();

    std::unique_ptr<Database_Project> m_dbp;
};
}
