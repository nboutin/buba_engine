//! \file	buba.cpp
//! \date
//! \author
//! \copyright
//!
//! Software Component:

#include "buba.h"
#include "database_project.h"
#include "importer_ofx.h"

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;
using namespace buba;

Budget_Battle::Budget_Battle() {}
Budget_Battle::~Budget_Battle() {}

bool Budget_Battle::create_project(const std::string& pathname)
{
    m_dbp = std::make_unique<Database_Project>(pathname);
    return true;
}

bool Budget_Battle::open_project(const std::string& pathname)
{
    m_dbp = std::make_unique<Database_Project>(pathname, db_connection_e::OPEN);
    return true;
}

bool Budget_Battle::import_ofx(const std::string& pathname)
{
    Importer_OFX importer;

    importer.process(pathname, m_dbp);

    return true;
}

std::vector<Bank_t> Budget_Battle::get_banks() const
{
    if(!m_dbp)
        return {};

    return m_dbp->get_banks();
}

std::vector<Account_t> Budget_Battle::get_accounts() const
{
    if(!m_dbp)
        return {};

    return m_dbp->get_accounts();
}

std::vector<Transaction_t> Budget_Battle::get_transactions() const
{
    if(!m_dbp)
        return {};

    return m_dbp->get_transactions();
}

bool Budget_Battle::set_bank_name(std::uint32_t bank_id, const std::string& name)
{
    if(!m_dbp)
        return false;

    return m_dbp->set_bank_name(bank_id, name);
}

bool Budget_Battle::set_account_name(const std::string& number, const std::string& name)
{
    if(!m_dbp)
        return false;

    return m_dbp->set_account_name(number, name);
}

std::vector<Label_t> Budget_Battle::get_labels() const
{
    if(!m_dbp)
        return {};

    return m_dbp->get_labels();
}

std::vector<Category_t> Budget_Battle::get_categories() const
{
    if(!m_dbp)
        return {};

    return m_dbp->get_categories();
}

bool Budget_Battle::add_label(const std::string& name)
{
    if(!m_dbp)
        return false;

    return m_dbp->add_label(name);
}
