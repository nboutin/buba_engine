//! \file buba.h
//! \date 29/04/2019
//! \author nboutin
//! \copyright
//!
//! Software Component: BuBa_engine

#pragma once

#include <memory>
#include <string>

namespace buba
{
class Database_Project;

class Budget_Battle
{
public:
    Budget_Battle();
    ~Budget_Battle();

    bool create_project(const std::string& pathname);
    //	bool open_project();

private:
    std::unique_ptr<Database_Project> m_dbp;
};
}
