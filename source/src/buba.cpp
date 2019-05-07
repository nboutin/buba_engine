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

    auto stmttrnrs = tree.get_child("OFX.BANKMSGSRSV1.STMTTRNRS");

    for(auto a : stmttrnrs)
    {
        cout << "a:" << a.first << ":" << a.second.data() << endl;

        if(a.first == "STMTRS")
        {
            for(auto b : a.second)
            {
                cout << "b:" << b.first << ":" << b.second.data() << endl;

                if(b.first == "BANKACCTFROM")
                {
                    auto branch   = b.second.get("BRANCH", "");
                    auto branchid = b.second.get("BRANCHID", "");

                    //                    cout << "branch:" << branch << endl;
                    //                    cout << "branchid:" << branchid << endl;

                    m_dbp->insert_bank(stoi(branchid));

                    auto acctid = b.second.get("ACCTID", "");
                }
                else if(b.first == "BANKTRANLIST")
                {
                    for(auto c : b.second)
                    {
                        cout << "c:" << c.first << ":" << c.second.data() << endl;

                        string fitid, date, description;
                        double amount = 0;

                        if(c.first == "STMTTRN")
                        {
                            for(auto d : c.second)
                            {
                                if(d.first == "FITID")
                                {
                                    fitid = d.second.data();
                                }
                                else if(d.first == "DTPOSTED")
                                {
                                    date = d.second.data();
                                }
                                else if(d.first == "TRNAMT")
                                {
                                    amount = strtod(d.second.data().c_str(), nullptr);
                                }
                                // Hopefully NAME is last in STMTTRN structure
                                else if(d.first == "NAME")
                                {
                                    description = d.second.data();
                                    m_dbp->insert_transaction(fitid, date, description, amount);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

#if 0
	auto operations_tree = tree.get_child("OFX.BANKMSGSRSV1.STMTTRNRS.STMTRS.BANKTRANLIST.STMTTRN");

	string fitid, date, description;
	double amount = 0;

	for(auto i : operations_tree)
	{
		//        cout << "i:" << i.first << ":" << i.second.data() << endl;

		if(i.first == "FITID")
		{
			fitid = i.second.data();
		}
		else if(i.first == "DTPOSTED")
		{
			date = i.second.data();
		}
		else if(i.first == "TRNAMT")
		{
			amount = strtod(i.second.data().c_str(), nullptr);
		}
		// Hopefully NAME is last in STMTTRN structure
		else if(i.first == "NAME")
		{
			description = i.second.data();
			m_dbp->insert_transaction(fitid, date, description, amount);
		}
	}
#endif

    return true;
}

std::vector<Transaction_t> Budget_Battle::get_transactions_all() const
{
    return m_dbp->get_transactions_all();
}
