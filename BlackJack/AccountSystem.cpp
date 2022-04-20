#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "AccountSystem.h"
#include "FileSystem.h"
#include "Validation.h"
#include "CustomMath.h"
#include "MainMenu.h"
#include "Game.h"
using namespace std;
ifstream accountFile("AccountInfo.txt");

struct Account
{
	string username;
	int passcode = 0000;
	int chipBalance = 0000;
};

void AccountSystem::LogIn()
{
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
	ifstream accountFile("AccountInfo.txt");
	std::vector<Account> accounts;
	while (loopControl)
	{
		if (!accountFile)
		{
			cout << "The file in question does not exist \n";
			loopControl = false;
		}
		for (size_t i = 0; i < count; i++)
		{
			Account account;
			accountFile >> account.username >> account.passcode >> account.chipBalance;
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
					game.startGame(accounts[z].username, accounts[z].chipBalance);
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

void AccountSystem::SetBalance(int balanceChange, bool isWin, int playerBal)
{
	if (isWin)
	{
		playerBal += balanceChange;
	}
	else if (isWin == false)
	{
		playerBal -= balanceChange;
	}
	/*Line Counter*/
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
}