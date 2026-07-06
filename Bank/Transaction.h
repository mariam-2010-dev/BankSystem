#pragma once
#include "Global.h"
#include "Utility.h"

short ReadTransactionOption();

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <sClient>& vClients);

void PrintClientRecordBalanceLine(sClient& Client);