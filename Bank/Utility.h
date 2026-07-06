#pragma once
#include "Global.h"

void AddLineToFile(string FileName, string Line);

vector<string> SplitString(string Line, string Delim = "#//#");

sClient ConvertLineToRecord(string Line);

stUser ConvertUserLineToRecord(string Line);

string ConvertRecordToLine(sClient Client, string Separator = "#//#");

string ConvertUserRecordToLine(stUser User, string Separator = "#//#");

bool CheckAccessPermission(enMainMenuPermissions Permission);

void ShowAccessDeniedMessage();

int ReadPermissionsToSet();