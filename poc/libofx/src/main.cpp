
#include <libofx/libofx.h>

#include <iostream>

using namespace std;

int account_cb(const struct OfxAccountData data, void*);
int transaction_cb(const struct OfxTransactionData data, void* transaction_data);

int main()
{
    LibofxContextPtr ctxt = libofx_get_new_context();

    //    ofx_set_account_cb(ctxt, &account_cb, nullptr);

    ofx_set_transaction_cb(ctxt, &transaction_cb, nullptr);

    libofx_proc_file(ctxt, "poc/libofx/test3.ofx", OFX);
}

int transaction_cb(const struct OfxTransactionData data, void*)
{
    cout << "account_id:" << data.account_id << endl;
    cout << "fi_id:" << data.fi_id << endl;
    //    cout << "unique_id:" << data.unique_id<< endl;
    cout << "amount:" << data.amount << endl;
    cout << "name:" << data.name << endl;

    return 0;
}

int account_cb(const struct OfxAccountData data, void*)
{
    cout << "bank_id:" << data.bank_id << endl;
    cout << "broker_id:" << data.broker_id << endl;
    cout << "branch_id:" << data.branch_id << endl;
    cout << "account_id:" << data.account_id << endl;
    cout << "account_name:" << data.account_name << endl;
    cout << "account_number:" << data.account_number << endl;

    return 0;
}
