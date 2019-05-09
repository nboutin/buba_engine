
#include "importer_ofx.h"
#include "database_project.h"

#include <iostream>
using namespace std;

using namespace buba;

int account_cb(const struct OfxAccountData data, void* context);
int transaction_cb(const struct OfxTransactionData data, void* context);

Importer_OFX::Importer_OFX() { m_context = libofx_get_new_context(); }

Importer_OFX::~Importer_OFX() { libofx_free_context(m_context); }

bool Importer_OFX::process(const std::string& pathname, std::unique_ptr<Database_Project>& dbp)
{
    (void) dbp;

    ofx_set_account_cb(m_context, &account_cb, dbp.get());
    ofx_set_transaction_cb(m_context, &transaction_cb, dbp.get());

    libofx_proc_file(m_context, pathname.c_str(), OFX);

    return true;
}

int account_cb(const struct OfxAccountData data, void* context)
{
    Database_Project* dbp = reinterpret_cast<Database_Project*>(context);

    //    cout << "|" << data.bank_id << "|" << data.broker_id << "|" << data.branch_id << "|"
    //         << data.account_id << "|" << data.account_name << "|" << data.account_number << endl;

    dbp->insert_bank(std::stoi(std::string(data.branch_id)));

    return 0;
}

int transaction_cb(const struct OfxTransactionData data, void* context)
{
    (void) data;
    (void) context;
    return 0;
}
