#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

const string FileName = "Clients.txt";

void ShowMainScreen();

void ShowTransactionScreen();

enum enMainInfoScreen { eShowclientslist = 1, eAddNewClients = 2, eDeleteClient = 3, eUpdateClientInfo = 4, eFindClient = 5, eTransaction = 6, eExit = 7 };

enum enTransaction { eDeposit = 1, ewithrdaw = 2, eTotalBalance = 3, eMainInfoScreen = 4 };

struct stClient
{
	string AccountNumber;
	string PinCode;
	string FullName;
	string PhoneNumber;
	double AccountBalance = 0;
	bool MarkForDelete = false;
};

vector<string> Split(string UserString, string deilma)
{
	vector <string> ElmentString;

	short pos = 0;
	string sword;

	while ((pos = UserString.find(deilma)) != std::string::npos)
	{
		sword = UserString.substr(0, pos);

		if (sword != "") {
			ElmentString.push_back(sword);
		}
		UserString.erase(0, pos + deilma.length());
	}
	if (UserString != "") {
		ElmentString.push_back(UserString);
	}

	return ElmentString;
}

stClient ConvertLineToRecord(string Record, string Spreator = "#//#")
{
	stClient Client;
	vector<string> vString = Split(Record, "#//#");

	Client.AccountNumber = vString[0];
	Client.PinCode = vString[1];
	Client.FullName = vString[2];
	Client.PhoneNumber = vString[3];
	Client.AccountBalance = stod(vString[4]);


	return Client;
}

vector<stClient> LoadDataToFile(string FileName)
{
	vector <stClient> vClients;
	std::fstream myfile;

	myfile.open(FileName, std::ios::in);

	if (myfile.is_open())
	{
		string Line;
		stClient Client;


		while (getline(myfile, Line))
		{
			Client = ConvertLineToRecord(Line);
			vClients.push_back(Client);
		}
		myfile.close();

	}

	return vClients;
}

void AddDataToFile(string Client, string FileName)
{
	std::fstream file;
	file.open(FileName, std::ios::out | std::ios::app);

	if (file.is_open()) {
		file << Client << endl;
	}
	file.close();
}

void PrintRecord(stClient& Client)
{
	cout << "| " << setw(15) << Client.AccountNumber;
	cout << "| " << setw(10) << Client.PinCode;
	cout << "| " << setw(40) << Client.FullName;
	cout << "| " << setw(12) << Client.PhoneNumber;
	cout << "| " << setw(12) << Client.AccountBalance;
}

void PrintBalanceRecord(stClient& Client)
{
	cout << "| " << setw(15) << Client.AccountNumber;
	cout << "| " << setw(40) << Client.FullName;
	cout << "| " << setw(12) << Client.AccountBalance;
}

void PrintAllClientsData(vector <stClient>& vClients)
{
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	for (stClient& Client : vClients)
	{
		PrintRecord(Client);
		cout << endl;
	}
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{
	vector <stClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);//read Mode
	if (MyFile.is_open())
	{
		string Line;
		stClient Client;
		while (getline(MyFile, Line))
		{
			Client = ConvertLineToRecord(Line);
			if (Client.AccountNumber == AccountNumber)
			{
				MyFile.close();
				return true;
			}
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return false;
}

stClient ReadNewClient()
{
	string AccountNumber;
	stClient Client;

	Client.AccountNumber = AccountNumber;

	cout << "Enter a new Account number : ";
	getline(cin >> ws, Client.AccountNumber);

	while (ClientExistsByAccountNumber(Client.AccountNumber, FileName))
	{
		cout << "(" << Client.AccountNumber << ") is already exist , Enter a new Account number :";
		getline(cin >> ws, Client.AccountNumber);

	}
	cout << "\nEnter PinCode ? ";
	getline(cin, Client.PinCode);

	cout << "\nEnter Full Name ? ";
	getline(cin, Client.FullName);


	cout << "\nEnter Phone Number ? ";
	getline(cin, Client.PhoneNumber);


	cout << "\nEnter Account Balance ? ";
	cin >> Client.AccountBalance;

	return Client;
}

string ConvertRecordToLine(stClient Client, string Spreator = "#//#")
{
	string RecordString = "";
	RecordString += Client.AccountNumber + Spreator;
	RecordString += Client.PinCode + Spreator;
	RecordString += Client.FullName + Spreator;
	RecordString += Client.PhoneNumber + Spreator;
	RecordString += to_string(Client.AccountBalance);

	return RecordString;
}

string ReadClientAccountNumber()
{
	string Name = " ";
	cout << "Please enter account number : ";
	cin >> Name;

	return Name;
}

bool FindClientAccountNumber(stClient& Clients, string AccountNumber, vector <stClient> vClients)
{
	for (stClient Client : vClients)
	{
		if (Client.AccountNumber == AccountNumber) {
			Clients = Client;
			return true;
		}
	}
	return false;
}

bool MarkTheAccountNumberForDelete(string AccountNumber, vector<stClient>& vClient)
{
	for (stClient& C : vClient)
	{
		if (C.AccountNumber == AccountNumber) {
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

vector<stClient> SaveDataToFile(stClient Client, vector<stClient>& vClient)
{

	std::fstream myfile;
	myfile.open(FileName, std::ios::out); //overwrite

	string DataLine;

	if (myfile.is_open())
	{
		for (stClient& C : vClient)
		{
			if (C.MarkForDelete == false) {

				DataLine = ConvertRecordToLine(C);
				myfile << DataLine << endl;
			}
		}
	}
	return vClient;
}

void PrintClientRecord(stClient Client)
{
	cout << "\n-------------------------------------\n";
	cout << "Account number : " << Client.AccountNumber << endl;
	cout << "PinCode : " << Client.PinCode << endl;
	cout << "FullName : " << Client.FullName << endl;
	cout << "PhoneNumber : " << Client.PhoneNumber << endl;
	cout << "AccountBalance : " << Client.AccountBalance;
	cout << "\n-------------------------------------";
}

bool DeleteClientByAccountNumber(string AccountNumber, vector<stClient>& vClient)
{
	stClient Clients;

	char Answer = 'n';

	if (FindClientAccountNumber(Clients, AccountNumber, vClient)) {

		PrintClientRecord(Clients);

		cout << "\n\nDo you want to delete this client ? y/n ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			MarkTheAccountNumberForDelete(AccountNumber, vClient);
			SaveDataToFile(Clients, vClient);

			vClient = LoadDataToFile(FileName);

			cout << "\n\nClient is deleted succssfully!";


			return true;
		}
	}
	else {
		cout << "\nThe account Number (" << AccountNumber << ")" << " is not found!";
		return false;
	}

}

stClient ChangeClientRecord(string AccountNumber, vector<stClient>& vClient)
{
	stClient Client;
	Client.AccountNumber = AccountNumber;

	//cin >> ws  - to delete the wide buffer;
	cout << "Enter PinCode ? ";
	getline(cin >> ws, Client.PinCode);

	cout << "Enter Full Name ? ";
	getline(cin, Client.FullName);

	cout << "Enter Phone Number ? ";
	getline(cin, Client.PhoneNumber);

	cout << "Enter Account Balance ? ";
	cin >> Client.AccountBalance;
	return Client;
}

bool UpdateClientByAccountNumber(string AcconutNumber, vector<stClient>& vClient)
{
	stClient Clients;

	char Answer = 'n';

	if (FindClientAccountNumber(Clients, AcconutNumber, vClient)) {

		PrintClientRecord(Clients);

		cout << "\n\nDo you want to update this client ? y/n ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			for (stClient& C : vClient) {
				if (C.AccountNumber == AcconutNumber) {
					C = ChangeClientRecord(AcconutNumber, vClient);
					break;
				}
			}
			SaveDataToFile(Clients, vClient);

			cout << "\n\nClient is update succssfully!";

			return true;
		}
	}
	else {
		cout << "\nThe account Number (" << AcconutNumber << ")" << " is not found!";
		return false;
	}
}

void BackToManu() {
	cout << "\n\nPress any key to go back to Main menu...";
	system("pause>0");
	ShowMainScreen();
}

void BackToTransactionManu() {
	cout << "\n\nPress any key to go back to Main menu...";
	system("pause>0");
	ShowTransactionScreen();
}

void DeleteClient()
{
	vector<stClient> vClient = LoadDataToFile(FileName);
	string AcconutNumber = ReadClientAccountNumber();
	DeleteClientByAccountNumber(AcconutNumber, vClient);

}

void AddNewClient(stClient& Client)
{
	cout << "\n----------------------------------\n";
	cout << "\t  Add new client";
	cout << "\n----------------------------------\n";

	cout << "\nPlease enter Client data : \n";

	Client = ReadNewClient();
	AddDataToFile(ConvertRecordToLine(Client), FileName);
}

void AddnewClients(stClient& Client)
{
	char MoreAgain = 'y';
	do {
		system("cls");
		cout << "Adding new client : " << endl;

		AddNewClient(Client);

		cout << "The data sucssfully added ,Do you want to add more client ?  ";
		cin >> MoreAgain;
	} while (MoreAgain == 'y' || MoreAgain == 'Y');

}

void ShowClientList(stClient& Client)
{
	vector<stClient> vString = LoadDataToFile(FileName);
	PrintAllClientsData(vString);
}

void UpdateClient(stClient& Client)
{
	cout << "\n----------------------------------\n";
	cout << "\t  Update client";
	cout << "\n----------------------------------\n";

	vector<stClient> vClient = LoadDataToFile(FileName);
	string AcconutNumber = ReadClientAccountNumber();

	UpdateClientByAccountNumber(AcconutNumber, vClient);

}

void FindClient(stClient& Client)
{
	cout << "\n----------------------------------\n";
	cout << "\t  Find client";
	cout << "\n----------------------------------\n";

	string AccountNumber = ReadClientAccountNumber();
	vector <stClient> vClients = LoadDataToFile(FileName);
	if (FindClientAccountNumber(Client, AccountNumber, vClients))
		PrintClientRecord(Client);
	else
		cout << "(" << AccountNumber << ")" << "not found";
}

void ShowEndClient()
{
	cout << "\n----------------------------------\n";
	cout << "\t  Program is end";
	cout << "\n----------------------------------\n";

}

int ReadPositiveNumber(string Message)
{
	int Number = 0;

	do {
		cout << Message;
		cin >> Number;
	} while (Number <= 0);
	return Number;
}

bool DepositBalanceByAccountNumber(string AcccountNumber, vector<stClient>& vClients, short DepositAmount)
{
	char Answer = 'n';

	cout << "Do you want to confirm this transaction ? y/n : ";
	cin >> Answer;

	if (tolower(Answer) == 'y')
	{
		for (stClient& C : vClients)
		{
			if (C.AccountNumber == AcccountNumber) {

				C.AccountBalance += DepositAmount;

				SaveDataToFile(C, vClients);

				cout << "\nDone succhssfully. New balance : " << C.AccountBalance;

				return true;
			}
		}


	}
	return false;
}

void ShowDepositScreen()
{
	cout << "\n----------------------------------\n";
	cout << "\t  Desposit screen";
	cout << "\n----------------------------------\n";

	stClient Client;
	string AccountNumber = ReadClientAccountNumber();
	vector <stClient> vClients = LoadDataToFile(FileName);

	while (!FindClientAccountNumber(Client, AccountNumber, vClients))
	{
		cout << "\nClient with ( " << AccountNumber << " ) is not exist in the system. ";
		cout << "\nPlease enter account number : ";
		cin >> AccountNumber;
	}

	PrintClientRecord(Client);

	int DepositNumber = 0;
	cout << "\nPlease enter deposit number : ";
	cin >> DepositNumber;

	DepositBalanceByAccountNumber(AccountNumber, vClients, DepositNumber);
}

void ShowWithdrawScreen()
{
	cout << "\n----------------------------------\n";
	cout << "\t  Withdraw screen";
	cout << "\n----------------------------------\n";

	stClient Client;
	string AccountNumber = ReadClientAccountNumber();
	vector <stClient> vClients = LoadDataToFile(FileName);


	while (!FindClientAccountNumber(Client, AccountNumber, vClients))
	{
		cout << "\nClient with ( " << AccountNumber << " ) is not exist in the system. ";
		cout << "\nPlease enter account number : ";
		cin >> AccountNumber;
	}

	PrintClientRecord(Client);

	int WithdrawAmount = 0;
	cout << "\nPlease enter withdraw number : ";
	cin >> WithdrawAmount;

	while (WithdrawAmount > Client.AccountBalance)
	{
		cout << "\namount excced the account balance , you can withdeaw up to : " << Client.AccountBalance;
		cout << "\nPlease enter withdraw number : ";
		cin >> WithdrawAmount;
	}

	DepositBalanceByAccountNumber(AccountNumber, vClients, WithdrawAmount * -1);
}

void PrintTotalBalanceClientsData()
{
	vector<stClient> vClients = LoadDataToFile(FileName);

	cout << "\n\t\t\t\t\Balance List (" << vClients.size() << ") Client(s).";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	double TotalBalance = 0;

	if (vClients.size() < 0)
		cout << "\nThere is no clients in the balance system.";
	else {
		for (stClient& C : vClients)
		{

			PrintBalanceRecord(C);
			TotalBalance += C.AccountBalance;

			cout << endl;
		}
	}

	"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;


	cout << "\t\t\t\t\t\t\t\t\Total Balance : " << TotalBalance;

}

void ShowTotalBalanceClientList()
{
	PrintTotalBalanceClientsData();
}

void PerformTransaction(enTransaction Transaction)
{

	stClient Client;
	switch (Transaction)
	{
	case enTransaction::eDeposit:
		system("cls");
		ShowDepositScreen();
		BackToTransactionManu();
		break;
	case enTransaction::ewithrdaw:
		system("cls");
		ShowWithdrawScreen();
		BackToTransactionManu();
		break;
	case enTransaction::eTotalBalance:
		system("cls");
		ShowTotalBalanceClientList();
		BackToTransactionManu();
		break;
	case enTransaction::eMainInfoScreen:
		ShowMainScreen();
	}
}

void PerformMainMenuOption(enMainInfoScreen MainInfoScreen)
{
	stClient Client;

	switch (MainInfoScreen)
	{
	case enMainInfoScreen::eShowclientslist:
		system("cls");
		ShowClientList(Client);
		BackToManu();
		break;
	case enMainInfoScreen::eAddNewClients:
		system("cls");
		AddnewClients(Client);
		BackToManu();
		break;
	case enMainInfoScreen::eDeleteClient:
		system("cls");
		DeleteClient();
		BackToManu();
		break;
	case enMainInfoScreen::eUpdateClientInfo:
		system("cls");
		UpdateClient(Client);
		BackToManu();
		break;
	case enMainInfoScreen::eFindClient:
		system("cls");
		FindClient(Client);
		BackToManu();
		break;
	case enMainInfoScreen::eTransaction:
		system("cls");
		ShowTransactionScreen();
		BackToManu();
		break;
	case enMainInfoScreen::eExit:
		system("cls");
		ShowEndClient();
		BackToManu();
		break;
	}
}

enMainInfoScreen ReadMainScreen()
{
	short Choose = 0;
	cout << "\n\nPlease choose what do your want from [1 to 7] ? ";
	cin >> Choose;

	return (enMainInfoScreen)Choose;
}

enTransaction ReadTransactionScreen()
{
	short Choose = 0;

	cout << "\n\nPlease choose what do your want from [1 to 4] ? ";
	cin >> Choose;

	return (enTransaction)Choose;
}

void ShowMainScreen()
{
	system("cls");
	cout << "\n==================================\n";
	cout << "\t  Main Info Screen";
	cout << "\n==================================\n";
	cout << "[1] Show clients list\n";
	cout << "[2] Add new clients\n";
	cout << "[3] Delete client\n";
	cout << "[4] Update client info\n";
	cout << "[5] Find client\n";
	cout << "[6] Transaction\n";
	cout << "[7] Exit\n";
	cout << "\n==================================";

	PerformMainMenuOption((enMainInfoScreen)ReadMainScreen());

}

void ShowTransactionScreen()
{
	system("cls");
	cout << "\n==================================\n";
	cout << "\t  Transaction Menu Screen";
	cout << "\n==================================\n";
	cout << "[1] Deposit\n";
	cout << "[2] Withdraw\n";
	cout << "[3] Total Balance\n";
	cout << "[4] Main Info Menu \n";
	cout << "\n==================================";

	PerformTransaction((enTransaction)ReadTransactionScreen());
}

int main()
{
	ShowMainScreen();
	return 0;
}
