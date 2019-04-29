//! \file	buba.cpp
//! \date
//! \author
//! \copyright
//!
//! Software Component:

#include "buba.h"

using namespace buba;

bool Budget_Battle::create_project(const std::string& pathname)
{
	m_dbp = std::make_unique<Database_Project>(pathname);
	return true;
}
