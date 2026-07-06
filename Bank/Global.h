#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

struct sClient {
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};


struct stUser {
	string UserName;
	string Password;
	int Permission;
	bool MarkForDelete = false;
};


enum enMainMenuOptions {
	eListClients = 1, eAddClient = 2,
	eDeleteClient = 3, eUpdateClient = 4,
	eFindClient = 5, eTransaction = 6,
	eManageUsers = 7, eLogout = 8
};

enum enTransactionOptions {
	eDeposit = 1, eWithdraw = 2,
	eTotalBalance = 3, eMain_Menu = 4
};

enum enManageUserOption {
	eListUsers = 1, eAddUser = 2, eDeleteUser = 3,
	eUpdateUser = 4, eFindUser = 5, eMainMenu = 6
};

enum enMainMenuPermissions {
	eAll = -1, pListClients = 1, pAddNewClient = 2,
	pDeleteClient = 4, pUpdateClient = 8, pFindClient = 16,
	pTransactions = 32, pManageUsers = 64
};

const string UsersFileName = "Users.txt";
const string ClientsFileName = "Clients.txt";

extern stUser CurrentUser;