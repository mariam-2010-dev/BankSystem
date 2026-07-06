#pragma once
#include "Global.h"
#include "Utility.h"

sClient ReadNewClient();
vector<sClient> LoadClientsDataFromFile(string FileName);
void AddNewClient();
void AddNewClients();

bool ClientExistsByAccountNumber(string AccountNumber, string FileName);
bool FindClientByAccountNumber(string AccountNumber, vector<sClient>& vClients, sClient& Client);

void PrintClientCard(const sClient& Client);
void PrintClientRecordLine(sClient Client);

void SaveClientsDataToFile(string FileName, vector<sClient>& vClients);
bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient>& vClients);
void UpdateClientByAccountNumber(string AccountNumber, vector<sClient>& vClients);

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients);
sClient ChangeClientRecord(string AccountNumber);
string ReadClientAccountNumber();