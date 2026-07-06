#include "User.h"
#include "Global.h"
#include "Utility.h"
#include <iostream>
#include <fstream>
#include <iomanip>

vector <stUser> LoadUsersDataFromFile(string FileName) {
	vector <stUser> Users;
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	if (MyFile.is_open()) {
		string Line;
		stUser User;
		while (getline(MyFile, Line)) {
			User = ConvertUserLineToRecord(Line);
			Users.push_back(User);
		}
		MyFile.close();
	}
	return Users;
}

bool FindUserByUserNameAndPassword(string Username, string Password, stUser& User) {
	vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);

	for (stUser& U : vUsers) {
		if (U.UserName == Username && U.Password == Password) {
			User = U;
			return true;
		}
	}
	return false;
}

bool LoadUserInfo(string Username, string Password) {
	if (FindUserByUserNameAndPassword(Username, Password, CurrentUser)) {
		return true;
	}
	else {
		return false;
	}
}

stUser ReadNewUser() {
	stUser User;

	cout << "Enter username: ";
	getline(cin >> ws, User.UserName);

	while (UserExistsByUserName(User.UserName, UsersFileName)) {
		cout << "\nUser With [" << User.UserName << "] already exist, Enter another username: ";
		getline(cin >> ws, User.UserName);
	}

	cout << "Enter Password: ";
	getline(cin, User.Password);

	User.Permission = ReadPermissionsToSet();

	return User;
}

bool UserExistsByUserName(string UserName, string FileName) {
	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open()) {
		string Line;
		stUser User;

		while (getline(MyFile, Line)) {
			User = ConvertUserLineToRecord(Line);
			if (User.UserName == UserName) {
				MyFile.close();
				return true;
			}
		}
		MyFile.close();
	}
	return false;
}

void AddNewUser() {
	stUser User;
	User = ReadNewUser();
	AddLineToFile(UsersFileName, ConvertUserRecordToLine(User));
}

void AddNewUsers() {
	char AddMore = 'Y';
	do {
		cout << "Adding new user:\n\n";
		AddNewUser();
		cout << "User added successfully, do you want to add more? Y/N: ";
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}

string ReadUserName() {
	string UserName = "";
	cout << "\nPlease enter username: ";
	cin >> UserName;
	return UserName;
}

bool FindUserByUserName(string UserName, vector <stUser>& vUsers, stUser& User) {
	for (stUser& U : vUsers) {
		if (U.UserName == UserName) {
			User = U;
			return true;
		}
	}
	return false;
}

void PrintUserCard(stUser User) {
	cout << "The following are the user details:\n";
	cout << "----------------------------------------------------";
	cout << "\nUserName: " << User.UserName;
	cout << "\nPassword: " << User.Password;
	cout << "\nPermissions: " << User.Permission;
	cout << "\n----------------------------------------------------\n";
}

bool MarkUserForDeleteByUserName(string UserName, vector <stUser>& vUsers) {
	for (stUser& U : vUsers) {
		if (U.UserName == UserName) {
			U.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

vector <stUser> SaveUsersDataToFile(string FileName, vector <stUser> & vUsers) {
	fstream MyFile;
	MyFile.open(FileName, ios::out);

	string Line;

	if (MyFile.is_open()) {
		for (stUser& U : vUsers) {
			if (U.MarkForDelete == false) {
				Line = ConvertUserRecordToLine(U);
				MyFile << Line << endl;
			}
		}
		MyFile.close();
	}
	return vUsers;
}

bool DeleteUserByUserName(string UserName, vector <stUser>& vUsers) {
	if (UserName == "Admin") {
		cout << "\n\nYou can not delete this user.";
		return false;
	}

	stUser User;
	char Answer = 'N';

	if (FindUserByUserName(UserName, vUsers, User)) {
		PrintUserCard(User);

		cout << "\n\nAre you sure you want delete this User: Y/N: ";
		cin >> Answer;

		if (toupper(Answer) == 'Y') {
			MarkUserForDeleteByUserName(UserName, vUsers);
			SaveUsersDataToFile(UsersFileName, vUsers);

			vUsers = LoadUsersDataFromFile(UsersFileName);
			cout << "\n\nUser deleted successfully.";
			return true;
		}
	}
	else {
		cout << "\nUser with Username (" << UserName << ") is Not Found!";
		return false;
	}
}

stUser ChangeUserRecord(string UserName) {
	stUser User;
	User.UserName = UserName;

	cout << "\n\nEnter new password: ";
	getline(cin >> ws, User.Password);

	User.Permission = ReadPermissionsToSet();

	return User;
}

bool UpdateUserByUserName(string UserName, vector <stUser>& vUsers) {
	stUser User;
	char Answer = 'n';

	if (FindUserByUserName(UserName, vUsers, User)) {
		PrintUserCard(User);
		cout << "\n\nAre you sure you want update this User? Y/N: ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y') {
			for (stUser& U : vUsers) {
				if (U.UserName == UserName) {
					U = ChangeUserRecord(UserName);
					break;
				}
			}
		}
		SaveUsersDataToFile(UsersFileName, vUsers);
		cout << "\n\nUser Updated Successfully.";
		return true;
	}
	else {
		cout << "\nUser with username (" << UserName << ") is Not Found!";
		return false;
	}
}