#include "Utility.h"
#include "Client.h"
#include "User.h"
#include "Transaction.h"
#include "Global.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

void ShowMainMenu();
void ShowTransactionMenu();
void ShowManageUsersMenu();
void Login();

stUser CurrentUser;

short ReadManageUserOption() {
	cout << "Choose what do you want to do? [1 to 6]: ";
	short Option;
	cin >> Option;
	return Option;
}

short ReadMainMenuOption() {
	short Option = 0;

	while(true) {
		cout << "Choose What do you want to do? [1:8]? ";
		cin >> Option;
		if (cin.fail() || Option < 1 || Option > 8) {
			cin.clear();
			cin.ignore();
			cout << "Invalid input! Please enter a number between 1 and 8. ";
		}
		else {
			return Option;
		}
	}
}



void GoBackToMainMenu() {
	cout << "\n\nPress any key to go back to Main Menu...";
	system("pause>0");
	ShowMainMenu();
}

void GoBackToTransactionMenu() {
	cout << "\n\nPress any key to go back to Transactions Menu...";
	system("Pause>0");
	ShowTransactionMenu();
}

void GoBackTOManageUserMenu() {
	cout << "\n\nPress any key to go back to Manage Users Menu...";
	system("pause>0");
	ShowManageUsersMenu();
}



void ShowDepositScreen() {
	cout << "\n-----------------------------------\n";
	cout << "\tDeposit Screen";
	cout << "\n-----------------------------------\n";

	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	sClient Client;

	string AccountNumber = ReadClientAccountNumber();
	while (!FindClientByAccountNumber(AccountNumber, vClients, Client)) {
		cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
		AccountNumber = ReadClientAccountNumber();
	}

	PrintClientCard(Client);

	double Amount = 0;
	cout << "\nPlease enter deposit amount? ";
	cin >> Amount;

	DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);
}

void ShowWithdrawScreen() {
	cout << "\n-----------------------------------\n";
	cout << "\tWithdraw Screen";
	cout << "\n-----------------------------------\n";
	sClient Client;
	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
			AccountNumber = ReadClientAccountNumber();
	}
	PrintClientCard(Client);
	double Amount = 0;
	cout << "\nPlease enter withdraw amount? ";
	cin >> Amount;

	while (Amount > Client.AccountBalance) {
		cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
		cout << "Please enter another amount? ";
		cin >> Amount;
	}

	DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);
}



void ShowTotalBalancesScreen() {
	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	double TotalBalances = 0;
	if (vClients.size() == 0)
		cout << "\t\t\t\tNo Clients Available In the System!";
	else
		for (sClient Client : vClients)
		{
			PrintClientRecordBalanceLine(Client);
			TotalBalances += Client.AccountBalance;
			cout << endl;
		}
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "\t\t\t\t\t\t Total Balances = " << TotalBalances;
	
}

void ShowAllClientsScreen() {
	if (!CheckAccessPermission(enMainMenuPermissions::pListClients))
	{
		ShowAccessDeniedMessage();
		return;
	}
	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	if (vClients.size() == 0) {
		cout << "\t\t\t\tNo Clients Available In the System!";
	}
	else {
		for (const sClient& C : vClients) {
			PrintClientRecordLine(C);
			cout << endl;
		}
	}
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}

void ShowAddNewClientsScreen() {
	if (!CheckAccessPermission(enMainMenuPermissions::pAddNewClient))
	{
		ShowAccessDeniedMessage();
		return;
	}
	cout << "\n-----------------------------------\n";
	cout << "\tAdd New Clients Screen";
	cout << "\n-----------------------------------\n";

	AddNewClients();
}

void ShowDeleteClientScreen() {
	if (!CheckAccessPermission(enMainMenuPermissions::pDeleteClient))
	{
		ShowAccessDeniedMessage();
		return;
	}
	cout << "\n-----------------------------------\n";
	cout << "\tDelete Client Screen";
	cout << "\n-----------------------------------\n";

	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	DeleteClientByAccountNumber(AccountNumber, vClients);
}

void ShowUpdateClientScreen() {
	if (!CheckAccessPermission(enMainMenuPermissions::pUpdateClient))
	{
		ShowAccessDeniedMessage();
		return;
	}
	cout << "\n-----------------------------------\n";
	cout << "\tUpdate Client Info Screen";
	cout << "\n-----------------------------------\n";

	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	UpdateClientByAccountNumber(AccountNumber, vClients);
}

void ShowFindClientScreen() {
	if (!CheckAccessPermission(enMainMenuPermissions::pFindClient))
	{
		ShowAccessDeniedMessage();
		return;
	}
	cout << "\n-----------------------------------\n";
	cout << "\tFind Client Screen";
	cout << "\n-----------------------------------\n";

	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	sClient Client;
	string AccountNumber = ReadClientAccountNumber();
	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
		PrintClientCard(Client);
	else
		cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";
}



void PrintUserRecordLine(stUser User) {
	cout << "| " << left << setw(15) << User.UserName;
	cout << "| " << left << setw(10) << User.Password;
	cout << "| " << left << setw(40) << User.Permission;
}

void ShowListUsersScreen() {
	vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
	cout << "\n\t\t\t\t\tUsers List (" << vUsers.size() << ") User(s).";
	cout << "\n------------------------------------------------------------------------------------------------------\n";

	cout << "| " << left << setw(15) << "User Name";
	cout << "| " << left << setw(10) << "Password";
	cout << "| " << left << setw(40) << "Permissions";
	cout << "\n------------------------------------------------------------------------------------------------------\n";

	if (vUsers.size() == 0) {
		cout << "\t\t\t\tNo users available in the system!";
	}
	else {
		for (stUser & User : vUsers) {
			PrintUserRecordLine(User);
			cout << endl;
		}
		cout << "\n------------------------------------------------------------------------------------------------------";
		cout << endl;
	}
}

void ShowAddNewUserScreen() {
	cout << "\n---------------------------------------\n";
	cout << "\tAdd New User Screen";
	cout << "\n---------------------------------------\n";

	AddNewUsers();
}


void ShowDeleteUserScreen() {
	cout << "\n-------------------------------------------------------\n";
	cout << "\tDelete Users Screen";
	cout << "\n-------------------------------------------------------\n";

	vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
	string UserName = ReadUserName();
	DeleteUserByUserName(UserName, vUsers);
}

void ShowUpdateUserScreen() {
	cout << "\n-------------------------------------------------------\n";
	cout << "\tUpdate Users Screen";
	cout << "\n-------------------------------------------------------\n";

	vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
	string UserName = ReadUserName();

	UpdateUserByUserName(UserName, vUsers);
}

void ShowFindUserScreen() {
	cout << "\n-------------------------------------------------------\n";
	cout << "\tFind Users Screen";
	cout << "\n-------------------------------------------------------\n";

	vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
	stUser User;
	string UserName = ReadUserName();

	if (FindUserByUserName(UserName, vUsers, User))
		PrintUserCard(User);
	else
		cout << "\nUser with Username [" << UserName << "] is not found!";
}

void PerformManageUsersMenuOptions(enManageUserOption ManageUserMenuOption) {
	switch (ManageUserMenuOption) {
	case enManageUserOption::eListUsers:
		system("cls");
		ShowListUsersScreen();
		GoBackTOManageUserMenu();
		break;
	case enManageUserOption::eAddUser:
		system("cls");
		ShowAddNewUserScreen();
		GoBackTOManageUserMenu();
		break;
	case enManageUserOption::eDeleteUser:
		system("cls");
		ShowDeleteUserScreen();
		GoBackTOManageUserMenu();
		break;
	case enManageUserOption::eUpdateUser:
		system("cls");
		ShowUpdateUserScreen();
		GoBackTOManageUserMenu();
		break;
	case enManageUserOption::eFindUser:
		system("cls");
		ShowFindUserScreen();
		GoBackTOManageUserMenu();
		break;
	case enManageUserOption::eMainMenu:
		ShowMainMenu();
		break;
	}
}

void PerformTransactionMenuOption(enTransactionOptions TransactionOptions) {
	switch (TransactionOptions) {
	case enTransactionOptions::eDeposit:
		system("cls");
		ShowDepositScreen();
		GoBackToTransactionMenu();
		break;
	case enTransactionOptions::eWithdraw:
		system("cls");
		ShowWithdrawScreen();
		GoBackToTransactionMenu();
		break;
	case enTransactionOptions::eTotalBalance:
		system("cls");
		ShowTotalBalancesScreen();
		GoBackToTransactionMenu();
		break;
	case enTransactionOptions::eMain_Menu:
		ShowMainMenu();
		break;
	}
}

void PerformMainMenuOption(enMainMenuOptions MainMenuOption) {
	switch (MainMenuOption) {
	case enMainMenuOptions::eListClients:
		system("cls");
		ShowAllClientsScreen();
		GoBackToMainMenu();
		break;
	case enMainMenuOptions::eAddClient:
		system("cls");
		ShowAddNewClientsScreen();
		GoBackToMainMenu();
		break;
	case enMainMenuOptions::eDeleteClient:
		system("cls");
		ShowDeleteClientScreen();
		GoBackToMainMenu();
		break;
	case enMainMenuOptions::eUpdateClient:
		system("cls");
		ShowUpdateClientScreen();
		GoBackToMainMenu();
		break;
	case enMainMenuOptions::eFindClient:
		system("cls");
		ShowFindClientScreen();
		GoBackToMainMenu();
		break;
	case enMainMenuOptions::eTransaction:
		system("cls");
		ShowTransactionMenu();
		break;
	case enMainMenuOptions::eManageUsers:
		system("cls");
		ShowManageUsersMenu();
		break;
	case enMainMenuOptions::eLogout:
		system("cls");
		Login();
		break;
	}
}

void ShowManageUsersMenu() {
	if (!CheckAccessPermission(enMainMenuPermissions::pManageUsers))
	{
		ShowAccessDeniedMessage();
		return;
	}

	system("cls");
	cout << "===========================================\n";
	cout << "\t\tManage Users Menu Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] List Users.\n";
	cout << "\t[2] Add New User.\n";
	cout << "\t[3] Delete User.\n";
	cout << "\t[4] Update User.\n";
	cout << "\t[5] Find User.\n";
	cout << "\t[6] Main Menu.\n";
	cout << "===========================================\n";
	PerformManageUsersMenuOptions((enManageUserOption)ReadManageUserOption());
}

void ShowTransactionMenu() {
	if (!CheckAccessPermission(enMainMenuPermissions::pTransactions))
	{
		ShowAccessDeniedMessage();
		return;
	}

	system("cls");
	cout << "===========================================\n";
	cout << "\t\tTransactions Menue Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balances.\n";
	cout << "\t[4] Main Menue.\n";
	cout << "===========================================\n";

	PerformTransactionMenuOption((enTransactionOptions)ReadTransactionOption());
}

void ShowMainMenu() {

	system("cls");
	cout << "===========================================\n";
	cout << "\t\tMain Menue Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transaction.\n";
	cout << "\t[7] Manage Users.\n";
	cout << "\t[8] Logout.\n";
	cout << "\n===========================================\n";

	PerformMainMenuOption((enMainMenuOptions)ReadMainMenuOption());
}

void Login() {
	bool LoginFailed = false;

	string Username, Password;

	do {
		system("cls");
		cout << "-------------------------------------------------\n";
		cout << "\tLogin Screen\n";
		cout << "-------------------------------------------------\n";

		if (LoginFailed) {
			cout << "Invalid Username/Password!\n";
		}

		cout << "Enter Username: ";
		cin >> Username;

		cout << "Enter Password: ";
		cin >> Password;

		LoginFailed = !LoadUserInfo(Username, Password);

	} while (LoginFailed);
	ShowMainMenu();
}

int main() {
	Login();
	system("pause>0");
	return 0;
}