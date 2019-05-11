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

    bool create_project(const std::string& pathname);
    bool open_project(const std::string& pathname);

    bool import_ofx(const std::string& pathname);

    std::vector<Bank_t> get_banks() const;
    std::vector<Account_t> get_accounts() const;
    std::vector<Transaction_t> get_transactions() const;
    std::vector<Label_t> get_labels() const;
    std::vector<Category_t> get_categories() const;

    bool set_bank_name(std::uint32_t bank_id, const std::string& name);
    bool set_account_name(const std::string& number, const std::string& name);
    bool set_transaction_label(const std::string fitid, const std::string& label_name);
    bool set_label_category(const std::string& label, const std::string& category);

    bool add_label(const std::string& name);

private:
    std::unique_ptr<Database_Project> m_dbp;
};
}
