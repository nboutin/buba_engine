//! \file	database_project.h
//! \date
//! \author
//! \copyright
//!
//! Software Component:

#pragma once

#include <sqlite3.h>

#include <string>

namespace buba
{
class Database_Project
{
public:
    Database_Project(const std::string& pathname);

private:
    void create_table_operation();
    void create_table_category();
    void create_table_label();

    sqlite3* m_db;
};
}
