#include "Utility.h"

void AddLineToFile(string FileName, string Line) {
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);
	if (MyFile.is_open()) {
		MyFile << Line << endl;
		MyFile.close();
	}
}

vector <string> SplitString(string Line, string Delim) {
	vector <string> vStrings;
	string sWord;
	short pos = 0;
	while ((pos = Line.find(Delim)) != std::string::npos) {
		sWord = Line.substr(0, pos);
		if (sWord != "") {
			vStrings.push_back(sWord);
		}
		Line.erase(0, pos + Delim.length());
	}
	if (Line != "") {
		vStrings.push_back(Line);
	}
	return vStrings;
}

sClient ConvertLineToRecord(string Line) {
	vector <string> vStrings = SplitString(Line);
	sClient Client;
	Client.AccountNumber = vStrings[0];
	Client.PinCode = vStrings[1];
	Client.Name = vStrings[2];
	Client.Phone = vStrings[3];
	Client.AccountBalance = stod(vStrings[4]);
	return Client;
}

stUser ConvertUserLineToRecord(string Line) {
	stUser User;
	vector <string> vString = SplitString(Line);
	User.UserName = vString[0];
	User.Password = vString[1];
	User.Permission = stoi(vString[2]);

	return User;
}

string ConvertRecordToLine(sClient Client, string Separator) {
	string stClientRecord = "";
	stClientRecord += Client.AccountNumber + Separator;
	stClientRecord += Client.PinCode + Separator;
	stClientRecord += Client.Name + Separator;
	stClientRecord += Client.Phone + Separator;
	stClientRecord += to_string(Client.AccountBalance);
	return stClientRecord;
}

string ConvertUserRecordToLine(stUser User, string Separator) {
	string stUserRecord = "";
	stUserRecord += User.UserName + Separator;
	stUserRecord += User.Password + Separator;
	stUserRecord += to_string(User.Permission);

	return stUserRecord;
}

bool CheckAccessPermission(enMainMenuPermissions Permission) {
	if (CurrentUser.Permission == enMainMenuPermissions::eAll) {
		return true;
	}
	if ((Permission & CurrentUser.Permission) == Permission) {
		return true;
	}
	else {
		return false;
	}
}

void ShowAccessDeniedMessage() {
	cout << "\n------------------------------------\n";
	cout << "Access Denied, \nYou dont Have Permission To Do this, \nPlease Conact Your Admin.";
	cout << "\n------------------------------------\n";
}

int ReadPermissionsToSet() {
	int Permissions = 0;
	char Answer = 'n';

	cout << "\nDo you want to give full access? y/n: ";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y') {
		return -1;
	}

	cout << "\nDo you want to give access to:\n";

	cout << "\nShow Client List: Y/N: ";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y') {
		Permissions += enMainMenuPermissions::pListClients;
	}

	cout << "\nAdd New Client: Y/N: ";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y') {
		Permissions += enMainMenuPermissions::pAddNewClient;
	}

	cout << "\nDelete Client: Y/N: ";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y') {
		Permissions += enMainMenuPermissions::pDeleteClient;
	}

	cout << "\nUpdate Client: Y/N: ";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y') {
		Permissions += enMainMenuPermissions::pUpdateClient;
	}

	cout << "\nFind Client: Y/N: ";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y') {
		Permissions += enMainMenuPermissions::pFindClient;
	}

	cout << "\nTransactions: Y/N: ";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y') {
		Permissions += enMainMenuPermissions::pTransactions;
	}

	cout << "\nManage users: Y/N: ";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y') {
		Permissions += enMainMenuPermissions::pManageUsers;
	}
	return Permissions;
}
