//! \file buba.h
//! \date 29/04/2019
//! \author nboutin
//! \copyright
//!
//! Software Component: BuBa_engine

#pragma once

#include "database_project.h"

#include <memory>
#include <string>

namespace buba
{
class Budget_Battle
{
public:
	bool create_project(const std::string& pathname);
//	bool open_project();

private:
	std::unique_ptr<Database_Project> m_dbp;
};
}
