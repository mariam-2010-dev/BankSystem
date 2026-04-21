#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

const string FileName = "Clients.txt";

void ShowMainMenu();
void ShowTransactionMenu();

struct sClient {
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};

enum enMainMenuOptions {
	eListClients = 1, eAddClient = 2,
	eDeleteClient = 3, eUpdateClient = 4,
	eFindClient = 5, eTransaction = 6,
	eExit = 7
};

enum enTransactionOptions {
	eDeposite = 1, eWithdrow = 2,
	eTotalBalance = 3, eMainMenu = 4
};

void GoBackToMainMenu() {
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	ShowMainMenu();
}

short ReadMainMenuOption() {
	short Option = 0;

	while(true) {
		cout << "Choose What do you want to do? [1:7]? ";
		cin >> Option;
		if (cin.fail() || Option < 1 || Option > 7) {
			cin.clear();
			cin.ignore();
			cout << "Invalid input! Please enter a number between 1 and 7. ";
		}
		else {
			return Option;
		}
	}
}

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

vector <string> Splitstring(string Line, string Delim = "#//#") {
	vector <string> vStrings;
	string sWord;
	short pos = 0;
	while ((pos = Line.find(Delim)) != std::string::npos) {
		sWord = Line.substr(0, pos);
		if (sWord != "") {
			vStrings.push_back(sWord);
			Line.erase(0, pos + Delim.length());
		}
	}
	if (Line != "") {
		vStrings.push_back(Line);
	}
	return vStrings;
}

sClient ConvertLineToRecord(string Line) {
	vector <string> vStrings = Splitstring(Line);
	sClient Client;
	Client.AccountNumber = vStrings[0];
	Client.PinCode = vStrings[1];
	Client.Name = vStrings[2];
	Client.Phone = vStrings[3];
	Client.AccountBalance = stod(vStrings[4]);
	return Client;
}

vector <sClient> LoadClientsDataFromFile(string FileName) {
	vector <sClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	if (MyFile.is_open()) {
		string Line;
		sClient Client;
		while (getline(MyFile, Line)) {
			Client = ConvertLineToRecord(Line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return vClients;
}

void PrintClientRecordLine(sClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName) {
	vector <sClient> vClients = LoadClientsDataFromFile(FileName);

	for (const sClient& C : vClients) {
		if (C.AccountNumber == AccountNumber) {
			return true;
		}
	}

	return false;
}

sClient ReadNewClient() {
	sClient Client;
	cout << "Enter Account Number? ";
	getline(cin >> ws, Client.AccountNumber);
	while (ClientExistsByAccountNumber(Client.AccountNumber, FileName))
	{
		cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number ? ";
			getline(cin >> ws, Client.AccountNumber);
	}
	cout << "Enter PinCode? ";
	getline(cin, Client.PinCode);
	cout << "Enter Name? ";
	getline(cin, Client.Name);
	cout << "Enter Phone? ";
	getline(cin, Client.Phone);
	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;
	return Client;
}

string ConvertRecordToLine(sClient Client, string Separator = "#//#") {
	string stClientRecord = "";
	stClientRecord += Client.AccountNumber + Separator;
	stClientRecord += Client.PinCode + Separator;
	stClientRecord += Client.Name + Separator;
	stClientRecord += Client.Phone + Separator;
	stClientRecord += to_string(Client.AccountBalance);
	return stClientRecord;
}

void AddLineToFile(string FileName, string Line) {
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);
	if (MyFile.is_open()) {
		MyFile << Line << endl;
		MyFile.close();
	}
}

void AddNewClient() {
	sClient Client;
	Client = ReadNewClient();
	string Line = ConvertRecordToLine(Client);
	AddLineToFile(FileName, Line);
}

void AddNewClients() {
	char AddMore = 'Y';

	do {
		cout << "Adding new client:\n\n";

		AddNewClient();

		cout << "Client Added Successfully, do you want to add more clients ? Y / N ? ";
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}

string ReadClientAccountNumber() {

	string AccountNumber = "";
	cout << "\nPlease enter AccountNumber? ";
	cin >> AccountNumber;

	return AccountNumber;
}

bool FindClientByAccountNumber(string AccountNumber, vector <sClient>& vClients, sClient& Client) {
	for (const sClient& C : vClients) {
		if (C.AccountNumber == AccountNumber) {
			Client = C;
			return true;
		}
	}
	return false;
}

void PrintClientCard(const sClient& Client) {
	cout << "\nThe following are the client details:\n";
	cout << "-----------------------------------";
	cout << "\nAccout Number: " << Client.AccountNumber;
	cout << "\nPin Code : " << Client.PinCode;
	cout << "\nName : " << Client.Name;
	cout << "\nPhone : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance;
	cout << "\n-----------------------------------\n";
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients) {
	for (sClient& C : vClients) {
		if (C.AccountNumber == AccountNumber) {
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

void SaveCleintsDataToFile(string FileName, vector <sClient>& vClients) {
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	if (MyFile.is_open()) {
		string Line;
		for (sClient C : vClients) {
			if (C.MarkForDelete == false) {
				Line = ConvertRecordToLine(C);
				MyFile << Line << endl;
			}
		}
		MyFile.close();
	}
}

bool DeleteClientByAccountNumber(string AccountNumber, vector <sClient>& vClients) {
	char Answer = 'n';
	sClient Client;
	if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {
		PrintClientCard(Client);
		cout << "\n\nAre you sure you want to delete this client? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveCleintsDataToFile(FileName, vClients);
			
			vClients = LoadClientsDataFromFile(FileName);
			cout << "\n\nClient Deleted Successfully.";
			return true;
		}
	}
	else {
		cout << "\nClient with Account Number (" << AccountNumber
			<< ") is Not Found!";
		return false;
	}
}

sClient ChangeClientRecord(string AccountNumber) {
	sClient Client;

	Client.AccountNumber = AccountNumber;
	cout << "\n\nEnter PinCode? ";
	getline(cin >> ws, Client.PinCode);
	cout << "Enter Name? ";
	getline(cin, Client.Name);
	cout << "Enter Phone? ";
	getline(cin, Client.Phone);
	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;

	return Client;
}

void UpdateClientByAccountNumber(string AccountNumber, vector <sClient>& vClients) {
	sClient Client;
	char Answer = 'Y';
	if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {
		PrintClientCard(Client);
		cout << "\n\nAre you sure you want update this client? y/n";
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y') {
			for (sClient& C : vClients) {
				if (C.AccountNumber == AccountNumber) {
					C = ChangeClientRecord(AccountNumber);
					break;
				}
			}
			SaveCleintsDataToFile(FileName, vClients);
			cout << "\n\nClient Updated Successfully.";
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
	}
}

void GoBackToTransactionMenu() {
	cout << "\n\nPress any key to go back to Transactions Menue...";
	system("Pause>0");
	ShowTransactionMenu();
}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <sClient>& vClients) {

	char Answer = 'n';
	cout << "\n\nAre you sure you want perfrom this transaction? y / n ? ";
	cin >> Answer;

	if (Answer == 'Y' || Answer == 'y') {
		for (sClient& C : vClients) {
			if (C.AccountNumber == AccountNumber) {
				C.AccountBalance += Amount;
				SaveCleintsDataToFile(FileName, vClients);
				return true;
			}
		}
		return false;
	}
	
}

void ShowDepositeScreen() {
	cout << "\n-----------------------------------\n";
	cout << "\tDeposit Screen";
	cout << "\n-----------------------------------\n";

	vector <sClient> vClients = LoadClientsDataFromFile(FileName);
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

void ShowWithdrowScreen() {
	cout << "\n-----------------------------------\n";
	cout << "\tWithdraw Screen";
	cout << "\n-----------------------------------\n";
	sClient Client;
	vector <sClient> vClients = LoadClientsDataFromFile(FileName);
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

void PrintClientRecordBalanceLine(sClient& Client) {
	cout << "| " << left << setw(15) << Client.AccountNumber;
	cout << "| " << left << setw(40) << Client.Name;
	cout << "| " << left << setw(12) << Client.AccountBalance;
}

void ShowTotalBalancesScreen() {
	vector <sClient> vClients = LoadClientsDataFromFile(FileName);
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

void PerformTransactionMenuOption(enTransactionOptions TransactionOptions) {
	switch (TransactionOptions) {
	case enTransactionOptions::eDeposite:
		system("cls");
		ShowDepositeScreen();
		GoBackToTransactionMenu();
		break;
	case enTransactionOptions::eWithdrow:
		system("cls");
		ShowWithdrowScreen();
		GoBackToTransactionMenu();
		break;
	case enTransactionOptions::eTotalBalance:
		system("cls");
		ShowTotalBalancesScreen();
		GoBackToTransactionMenu();
		break;
	case enTransactionOptions::eMainMenu:
		ShowMainMenu();
		break;
	}
}

void ShowAllClientsScreen() {
	vector <sClient> vClients = LoadClientsDataFromFile(FileName);
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
		cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout <<
		"\n_______________________________________________________";
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
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}

void ShowAddNewClientsScreen() {
	cout << "\n-----------------------------------\n";
	cout << "\tAdd New Clients Screen";
	cout << "\n-----------------------------------\n";

	AddNewClients();
}

void ShowDeleteClientScreen() {
	cout << "\n-----------------------------------\n";
	cout << "\tDelete Client Screen";
	cout << "\n-----------------------------------\n";

	vector <sClient> vClients = LoadClientsDataFromFile(FileName);
	string AccountNumber = ReadClientAccountNumber();
	DeleteClientByAccountNumber(AccountNumber, vClients);
}

void ShowUpdateClientScreen() {
	cout << "\n-----------------------------------\n";
	cout << "\tUpdate Client Info Screen";
	cout << "\n-----------------------------------\n";

	vector <sClient> vClients = LoadClientsDataFromFile(FileName);
	string AccountNumber = ReadClientAccountNumber();
	UpdateClientByAccountNumber(AccountNumber, vClients);
}

void ShowFindClientScreen() {
	cout << "\n-----------------------------------\n";
	cout << "\tFind Client Screen";
	cout << "\n-----------------------------------\n";

	vector <sClient> vClients = LoadClientsDataFromFile(FileName);
	sClient Client;
	string AccountNumber = ReadClientAccountNumber();
	if (FindClientByAccountNumber(AccountNumber, vClients,
		Client))
		PrintClientCard(Client);
	else
		cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";
}

void ShowEndScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tProgram Ends :-)";
	cout << "\n-----------------------------------\n";
}

void ShowTransactionMenu() {

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
	case enMainMenuOptions::eExit:
		system("cls");
		ShowEndScreen();
		GoBackToMainMenu();
		break;
	}
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
	cout << "\t[7] Exit.\n";
	cout << "===========================================\n";

	PerformMainMenuOption((enMainMenuOptions)ReadMainMenuOption());
}

int main() {
	ShowMainMenu();
}