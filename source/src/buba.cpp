//! \file	buba.cpp
//! \date
//! \author
//! \copyright
//!
//! Software Component:

#include "buba.h"
#include "database_project.h"
#include "parser_ofx.h"

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
    Parser_OFX parser(pathname);

    auto tree = parser.get_tree();

    auto operations_tree = tree.get_child("OFX.BANKMSGSRSV1.STMTTRNRS.STMTRS.BANKTRANLIST.STMTTRN");

    string date, description;
    double amount = 0;

    for(auto i : operations_tree)
    {
        //        cout << "i:" << i.first << ":" << i.second.data() << endl;

        if(i.first == "DTPOSTED")
        {
            date = i.second.data();
        }
        else if(i.first == "TRNAMT")
        {
            amount = strtod(i.second.data().c_str(), nullptr);
        }
        else if(i.first == "NAME")
        {
            description = i.second.data();
            m_dbp->insert_transaction(date, description, amount);
        }
    }

    return true;
}

std::vector<Transaction_t> Budget_Battle::get_transactions_all() const
{
    return m_dbp->get_transactions_all();
}
