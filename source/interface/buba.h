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
    std::uint32_t id;
    std::string name;
};

struct Transaction_t
{
    std::string fitid;
    std::string date;
    std::string description;
    double amount;
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
    std::vector<Transaction_t> get_transactions() const;

private:
    std::unique_ptr<Database_Project> m_dbp;
};
}
