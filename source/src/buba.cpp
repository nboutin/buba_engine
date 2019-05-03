//! \file	buba.cpp
//! \date
//! \author
//! \copyright
//!
//! Software Component:

#include "buba.h"
#include "database_project.h"
#include "parser_ofx.h"

using namespace buba;

Budget_Battle::Budget_Battle() {}
Budget_Battle::~Budget_Battle() {}

bool Budget_Battle::create_project(const std::string& pathname)
{
    m_dbp = std::make_unique<Database_Project>(pathname);
    return true;
}

bool Budget_Battle::import_ofx(const std::string& pathname)
{
    Parser_OFX parser(pathname);

    auto tree = parser.get_tree();

    m_dbp->insert_operation("03052019", "description field", 123.45);
    m_dbp->insert_operation("04052019", "description field again", -987.456);

    return true;
}
