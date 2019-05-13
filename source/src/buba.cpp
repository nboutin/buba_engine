//! \file	buba.cpp
//! \date
//! \author
//! \copyright
//!
//! Software Component:

#include "buba.h"
#include "database_project.h"
#include "importer_ofx.h"

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"

#include <cstdlib>
#include <string>

using namespace std;
using namespace buba;

Budget_Battle::Budget_Battle()
{
    auto file_logger = spdlog::basic_logger_mt("main", "/tmp/bubap.log");
    spdlog::set_default_logger(file_logger);
    spdlog::set_level(spdlog::level::debug);
    spdlog::flush_every(std::chrono::seconds(1));
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S:%e][%n][%-5l] %v");

    spdlog::info("");
    spdlog::info("Starting Budget Battle library");
}

Budget_Battle::~Budget_Battle() {}

bool Budget_Battle::project_create(const std::string& pathname)
{
    spdlog::info("{} {}", __func__, pathname);
    m_dbp = std::make_unique<Database_Project>(pathname);
    return true;
}

bool Budget_Battle::project_open(const std::string& pathname)
{
    spdlog::info("{} {}", __func__, pathname);
    m_dbp = std::make_unique<Database_Project>(pathname, db_connection_e::OPEN);
    return true;
}

void Budget_Battle::project_close()
{
    spdlog::info("{}", __func__);
    m_dbp.reset(nullptr);
}

bool Budget_Battle::import_ofx(const std::string& pathname)
{
    spdlog::info("{} {}", __func__, pathname);

    Importer_OFX importer;

    importer.process(pathname, m_dbp);

    return true;
}

std::vector<Bank_t> Budget_Battle::get_banks() const
{
    spdlog::info("{}", __func__);

    if(!m_dbp)
        return {};

    return m_dbp->get_banks();
}

std::vector<Account_t> Budget_Battle::get_accounts() const
{
    spdlog::info("{}", __func__);

    if(!m_dbp)
        return {};

    return m_dbp->get_accounts();
}

std::vector<Transaction_t> Budget_Battle::get_transactions() const
{
    spdlog::info("{}", __func__);

    if(!m_dbp)
        return {};

    return m_dbp->get_transactions();
}

std::vector<Transaction_t> Budget_Battle::get_transactions_without_label() const
{
    spdlog::info("{}", __func__);

    if(!m_dbp)
        return {};

    return m_dbp->get_transactions_without_label();
}

std::vector<Label_t> Budget_Battle::get_labels() const
{
    spdlog::info("{}", __func__);

    if(!m_dbp)
        return {};

    return m_dbp->get_labels();
}

std::vector<Category_t> Budget_Battle::get_categories() const
{
    spdlog::info("{}", __func__);

    if(!m_dbp)
        return {};

    return m_dbp->get_categories();
}

bool Budget_Battle::set_bank_name(std::uint32_t bank_id, const std::string& name)
{
    spdlog::info("{} {} {}", __func__, bank_id, name);

    if(!m_dbp)
        return false;

    return m_dbp->set_bank_name(bank_id, name);
}

bool Budget_Battle::set_account_name(const std::string& number, const std::string& name)
{
    spdlog::info("{} {} {}", __func__, number, name);

    if(!m_dbp)
        return false;

    return m_dbp->set_account_name(number, name);
}

bool Budget_Battle::set_transaction_label(const std::string fitid, const std::string& label_name)
{
    spdlog::info("{} {} {}", __func__, fitid, label_name);

    if(!m_dbp)
        return false;

    return m_dbp->set_transaction_label(fitid, label_name);
}

bool Budget_Battle::set_label_category(const std::string& label, const std::string& category)
{
    spdlog::info("{} {} {}", __func__, label, category);

    if(!m_dbp)
        return false;

    return m_dbp->set_label_category(label, category);
}

bool Budget_Battle::add_label(const std::string& name)
{
    spdlog::info("{} {}", __func__, name);

    if(!m_dbp)
        return false;

    return m_dbp->add_label(name);
}
