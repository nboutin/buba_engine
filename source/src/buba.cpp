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

std::vector<Transaction_t> Budget_Battle::get_transactions_all() const
{
    return m_dbp->get_transactions_all();
}
