
#include "importer_ofx.h"
#include "database_project.h"

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"

#include <ctime>

using namespace std;
using namespace buba;

int account_cb(const struct OfxAccountData data, void* context);
int transaction_cb(const struct OfxTransactionData data, void* context);
int statement_cb(const struct OfxStatementData data, void* context);

Importer_OFX::Importer_OFX() { m_context = libofx_get_new_context(); }

Importer_OFX::~Importer_OFX() { libofx_free_context(m_context); }

bool Importer_OFX::process(const std::string& pathname, std::unique_ptr<Database_Project>& dbp)
{
    spdlog::info("{} {}", __func__, pathname);

    ofx_set_account_cb(m_context, &account_cb, dbp.get());
    ofx_set_transaction_cb(m_context, &transaction_cb, dbp.get());
    ofx_set_statement_cb(m_context, &statement_cb, dbp.get());

    libofx_proc_file(m_context, pathname.c_str(), OFX);

    return true;
}

int account_cb(const struct OfxAccountData data, void* context)
{
    Database_Project* dbp = reinterpret_cast<Database_Project*>(context);

    spdlog::debug("|{}|", data.branch_id);
    int bank_id = std::stoi(data.branch_id);
    dbp->insert_bank(bank_id, "");

    spdlog::debug("|{}|{}|", data.account_number, data.branch_id);
    dbp->insert_account(data.account_number, "", bank_id);

    return 0;
}

int transaction_cb(const struct OfxTransactionData data, void* context)
{
    Database_Project* dbp = reinterpret_cast<Database_Project*>(context);

    char date[64];
    strftime(date, 64, "%Y%m%d", std::localtime(&data.date_posted));

    spdlog::debug("|{}|{}|{}|{}|{}|",
                  data.fi_id,
                  date,
                  data.name,
                  data.amount,
                  data.account_ptr->account_number);

    dbp->insert_transaction(std::string(data.fi_id),
                            date,
                            std::string(data.name),
                            data.amount,
                            data.account_ptr->account_number);

    return 0;
}

int statement_cb(const struct OfxStatementData data, void* context)
{
    Database_Project* dbp = reinterpret_cast<Database_Project*>(context);
    (void) dbp;

    spdlog::debug("|{}|{}|", data.account_ptr->account_number, data.ledger_balance);
    dbp->set_account_balance(data.account_ptr->account_number, data.ledger_balance);

    return 0;
}
