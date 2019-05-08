
#include <libofx/libofx.h>

#include <ctime>
#include <iomanip>
#include <iostream>

using namespace std;

int account_cb(const struct OfxAccountData data, void*);
int transaction_cb(const struct OfxTransactionData data, void* transaction_data);

int main()
{
    LibofxContextPtr ctxt = libofx_get_new_context();

    ofx_set_account_cb(ctxt, &account_cb, nullptr);

    ofx_set_transaction_cb(ctxt, &transaction_cb, nullptr);

    libofx_proc_file(ctxt, "poc/libofx/test3.ofx", OFX);
}

int transaction_cb(const struct OfxTransactionData data, void*)
{
    cout << data.account_ptr->bank_id << "|" << data.account_ptr->branch_id << "|"
         << data.account_ptr->account_number << "|" << data.fi_id << "|"
         << std::put_time(std::localtime(&data.date_posted), "%c %Z") << "|" << data.name << "|"
         << data.memo << "|" << data.amount << endl;

    return 0;
}

int account_cb(const struct OfxAccountData data, void*)
{
    cout << data.bank_id << "|" << data.broker_id << "|" << data.branch_id << "|" << data.account_id
         << "|" << data.account_name << "|" << data.account_number << endl;

    return 0;
}
