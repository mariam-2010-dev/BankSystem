#include "Transaction.h"
#include "Global.h"
#include "Client.h"
#include "Utility.h"
#include <iostream>
#include <fstream>
#include <iomanip>


short ReadTransactionOption() {
	short Option = 0;

	while (true) {
		cout << "Choose What do you want to do? [1:4]? ";
		cin >> Option;
		if (cin.fail() || Option < 1 || Option > 4) {
			cin.clear();
			cin.ignore();
			cout << "Invalid input! Please enter a number between 1 and 4. ";
		}
		else {
			return Option;
		}
	}
}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <sClient>& vClients) {

	char Answer = 'n';
	cout << "\n\nAre you sure you want perform this transaction? y / n ? ";
	cin >> Answer;

	if (Answer == 'Y' || Answer == 'y') {
		for (sClient& C : vClients) {
			if (C.AccountNumber == AccountNumber) {
				C.AccountBalance += Amount;
				SaveClientsDataToFile(ClientsFileName, vClients);
				return true;
			}
		}
		return false;
	}
	else {
		return false;
	}

}

void PrintClientRecordBalanceLine(sClient& Client) {
	cout << "| " << left << setw(15) << Client.AccountNumber;
	cout << "| " << left << setw(40) << Client.Name;
	cout << "| " << left << setw(12) << Client.AccountBalance;
}