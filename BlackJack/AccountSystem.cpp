#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <vector>
#include "AccountSystem.h"
#include "Validation.h"
#include "CustomMath.h"
#include "MainMenu.h"
#include "Game.h"
using namespace std;
struct Account
{
	string username;
	int passcode = 0000;
	int chipBalance = 0000;
};

void AccountSystem::LogIn()
{
	ifstream accountFile("AccountInfo.txt");
	Game game;
	Validation val;
	string attemptedUsername;
	int attemptedPasscode;
	bool loopControl = true;
	int count = 0;
	if (accountFile.is_open())
	{
		string line;
		while (!accountFile.eof())
		{
			getline(accountFile, line);
			count++;
		}
	}
	accountFile.close();
	ifstream accountFile2("AccountInfo.txt");
	std::vector<Account> accounts;
	while (loopControl)
	{
		if (!accountFile2)
		{
			cout << "The file in question does not exist \n";
			loopControl = false;
		}
		for (size_t i = 0; i < count; i++)
		{
			Account account;
			accountFile2 >> account.username >> account.passcode >> account.chipBalance;
			accounts.push_back(account);
		}
		int logInAttempts = 0;
		int logInMax = 5;
		bool loopControl2 = true;
		while (loopControl2)
		{
			if (logInAttempts == logInMax)
			{
				cout << "You have been locked out for too many failed attempts try again later" << endl;
				loopControl = false;
				loopControl2 = false;
			}
			else
			{
				cout << "Please Enter your Username: \n";
				cin >> attemptedUsername;
				attemptedPasscode = val.intValidation("Please Enter your Passcode:");
				int z = 0;
				bool isCorrect = false;
				while (z < count)
				{
					if (attemptedUsername == accounts[z].username && attemptedPasscode == accounts[z].passcode)
					{
						cout << "Welcome to the casino {" << attemptedUsername << "}!" << endl;
						loopControl2 = false;
						loopControl = false;
						isCorrect = true;
						break;
					}
					else
					{
						z++;
					}
				}
				if (isCorrect == true)
				{
					game.startGame(accounts[z].username, accounts[z].chipBalance, accounts[z].passcode);
				}
				else
				{
					logInAttempts++;
					cout << "Username or password is incorrect try again" << endl;
					cout << "You have " << logInMax - logInAttempts << " attempts left" << endl;
				}
			}
		}
	}
	
}



void AccountSystem::AccountCreator()
{
	MainMenu mm;
	CustomMath cusMath;
	Validation val;
	ifstream accountFile("AccountInfo.txt");
	int count = 0;
	if (accountFile.is_open())
	{
		string line;
		while (!accountFile.eof())
		{
			getline(accountFile, line);
			count++;
		}
	}
	accountFile.close();
	ifstream accountFile2("AccountInfo.txt");
	std::vector<Account> preAccounts;
	Account account;
	for (size_t i = 0; i < count; i++)
	{
		accountFile2 >> account.username >> account.passcode >> account.chipBalance;
		preAccounts.push_back(account);
	}
	accountFile2.close();
	int const passcodeLenReq = 4;
	bool loopControl = true;
	cout << "Welcome to the account creation center!" << endl;
	string newUsername;
	int newPasscode;
	while (loopControl)
	{
		int innerCount = count;
		cout << "The first step of creating an account is to choose a username!" << endl;
		cout << "Please enter a username: \n";
		cin >> newUsername;
		bool passCodeLoop = true;
		while (passCodeLoop)
		{
			newPasscode = val.intValidation("Please enter a new passcode! Your passcode must be 4 digits long:\n");
			int passcodeLen = cusMath.countDigit(newPasscode);
			if (passcodeLen != passcodeLenReq)
			{
				cout << "Your passcode must be " << passcodeLenReq << " digits long! Please try again" << endl;
			}
			else
			{
				passCodeLoop = false;
			}
		}
		bool isFail = false;
		for (size_t i = 0; i < innerCount; i++)
		{
			if (newUsername == preAccounts[i].username)
			{
				cout << "You cannot use this username as it is already in use, Please try again!" << endl;
				i = innerCount;
				isFail = true;
			}
			else
			{
				continue;
			}
		}
		if (isFail == true)
		{
			continue;
		}
		else
		{
			loopControl = false;
		}
	}
	int baseBalance = 25000;
	ofstream fileOutput;
	fileOutput.open("AccountInfo.txt", std::ios_base::app);
	fileOutput << "\n" << newUsername << " " << newPasscode << " " << baseBalance;
	cout << "Account created enjoy! Please log in with your details!" << endl;
	mm.mainMenu();
}

void AccountSystem::SetBalance(int balanceChange, bool isWin, int playerBal, string playerUserName, int playerPassCode)
{
	if (isWin)
	{
		playerBal = playerBal + balanceChange;
	}
	else if (isWin == false)
	{
		playerBal = playerBal - balanceChange;
	}
	/*Line Counter and reader*/
	
	ifstream accountFile3("AccountInfo.txt");
	int count = 0;
	if (accountFile3.is_open())
	{
		string line;
		while (!accountFile3.eof())
		{
			getline(accountFile3, line);
			count++;
		}
	}
	cout << count << endl;
	accountFile3.close();

	ifstream accFile("AccountInfo.txt");
	std::vector<Account> accounts2;
	Account account2;
	for (size_t p = 0; p < count; p++)
	{
		Account account2;
		accFile >> account2.username >> account2.passcode >> account2.chipBalance;
		accounts2.push_back(account2);
	}
	accFile.close();
	ifstream accFile2("AccountInfo.txt");
	string search = playerUserName;
	string line2;
	int whereLine = 0;
	size_t pos;
	while (!accFile2.eof())
	{
		while (accFile2.good())
		{
			getline(accFile2, line2); // get line from file
			pos = line2.find(search); // search
			if (pos != string::npos) // string::npos is returned if string is not found
			{
				cout << "Found!";
				cout << pos << endl;
				break;
			}
		}
		break;
	}
	accFile.close();
	ofstream accFileWrite;
	accFileWrite.open("AccountInfo.txt", std::ios_base::trunc);
	for (size_t i = 0; i < count; i++)
	{
		if (i == pos)
		{
			if (i == 0)
			{
				accFileWrite << playerUserName << " " << playerPassCode << " " << playerBal;
			}
			else
			{
				accFileWrite << "\n" << playerUserName << " " << playerPassCode << " " << playerBal;
			}
			
		}
		else
		{
			if (i == 0)
			{
				accFileWrite << accounts2[i].username << " " << accounts2[i].passcode << " " << accounts2[i].chipBalance;
			}
			else
			{
				accFileWrite << "\n" << accounts2[i].username << " " << accounts2[i].passcode << " " << accounts2[i].chipBalance;
			}
		}
	}
	accFileWrite.close();
	cout << "File saving done" << endl;
}