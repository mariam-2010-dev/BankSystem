#pragma once
#include "Global.h"
#include "Utility.h"

vector <stUser> LoadUsersDataFromFile(string FileName);

bool FindUserByUserNameAndPassword(string Username, string Password, stUser& User);

bool LoadUserInfo(string Username, string Password);

stUser ReadNewUser();

bool UserExistsByUserName(string UserName, string FileName);

void AddNewUser();

void AddNewUsers();

string ReadUserName();

bool FindUserByUserName(string UserName, vector <stUser> & vUsers, stUser& User);

void PrintUserCard(stUser User);

bool MarkUserForDeleteByUserName(string UserName, vector <stUser>& vUsers);

vector <stUser> SaveUsersDataToFile(string FileName, vector <stUser> & vUsers);

bool DeleteUserByUserName(string UserName, vector <stUser>& vUsers);

stUser ChangeUserRecord(string UserName);

bool UpdateUserByUserName(string UserName, vector <stUser>& vUsers);