
#include "importer_ofx.h"
#include "database_project.h"

#include <ctime>
#include <iomanip>
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

    cout << "|" << data.bank_id << "|" << data.broker_id << "|" << data.branch_id << "|"
         << data.account_id << "|" << data.account_name << "|" << data.account_number << endl;

    int bank_id = std::stoi(data.branch_id);
    dbp->insert_bank(bank_id, "");

    // 33 333 333 333
    //    int account_number = std::stoi(data.account_number);
    dbp->insert_account(data.account_number, "", bank_id);

    return 0;
}

int transaction_cb(const struct OfxTransactionData data, void* context)
{
    Database_Project* dbp = reinterpret_cast<Database_Project*>(context);

    //    cout << "|" << data.account_ptr->bank_id << "|" << data.account_ptr->branch_id << "|"
    //         << data.account_ptr->account_number << "|" << data.fi_id << "|"
    //         << std::put_time(std::localtime(&data.date_posted), "%c %Z") << "|" << data.name <<
    //         "|"
    //         << data.memo << "|" << data.amount << endl;

    char date[64];
    strftime(date, 64, "%Y%m%d", std::localtime(&data.date_posted));

    dbp->insert_transaction(std::string(data.fi_id),
                            date,
                            std::string(data.name),
                            data.amount,
                            data.account_ptr->account_number);

    return 0;
}
