#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "AccountSystem.h"
#include "FileSystem.h"
#include "Validation.h"
#include "CustomMath.h"
using namespace std;
Validation val;
CustomMath cusMath;
ifstream accountFile("AccountInfo.txt");

struct Account
{
	string username;
	int passcode;
	int chipBalance;
};

struct CurrentAccounts
{
	string currentUsername;
	int currentPasscode;
};

void AccountSystem::LogIn()
{
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
			accountFile>>account.username>>account.passcode>>account.chipBalance;
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
				std::vector<CurrentAccounts> currentAccounts;
				cout << "Please Enter your Username: \n";
				cin >> attemptedUsername;
				attemptedPasscode = val.intValidation("Please Enter your Passcode:");
				for (size_t i = 0; i < count; i++)
				{
					CurrentAccounts currentDetails;
					currentDetails.currentUsername = accounts[i].username;
					currentDetails.currentPasscode = accounts[i].passcode;
					currentAccounts.push_back(currentDetails);
					//string currentUsername = accounts[i].username;
					//int currentPasscode = accounts[i].passcode;
					if (attemptedUsername == currentAccounts[i].currentUsername && attemptedPasscode == currentAccounts[i].currentPasscode)
					{
						cout << "Welcome to the casino {" << currentAccounts[i].currentUsername << "}!" << endl;
						loopControl2 = false;
						loopControl = false;
						i = count;
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
	
}



void AccountSystem::AccountCreator()
{
	ifstream accountFile("AccountInfo.txt");
	Account account;
	bool loopControl = true;
	cout << "Welcome to the account creation center!" << endl;
	string newUsername;
	int newPasscode;
	while (loopControl)
	{
		cout << "The first step of creating an account is to choose a username!" << endl;
		cout << "Please enter a username: \n";
		cin >> newUsername;
		newPasscode = val.intValidation("Please enter a new passcode! Your passcode must be 4 digits long:\n");

	}
}
