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

// A struct to keep individual elements of the users data
struct Account
{
	string username;
	int passcode = 0000;
	int chipBalance = 0000;
};

void AccountSystem::LogIn() // log in function
{
	ifstream accountFile("AccountInfo.txt"); // opens account info text file
	Game game;
	Validation val; // instatiates game and validation classes
	string attemptedUsername;
	int attemptedPasscode;
	bool loopControl = true;
	int count = 0;
	if (accountFile.is_open()) // if the file is open run code
	{
		string line;
		while (!accountFile.eof()) // while not at end of file
		{
			getline(accountFile, line); // get the line from the file and store line in variable line
			count++; // + 1 to line count
		}
	}
	accountFile.close(); // close the file to reset
	ifstream accountFile2("AccountInfo.txt"); // re open to reset
	std::vector<Account> accounts; // vector of the Struct Account
	while (loopControl)
	{
		if (!accountFile2) // if the file doesnt exist big error
		{
			cout << "The file in question does not exist \n";
			loopControl = false;
		}
		for (size_t i = 0; i < count; i++) // Instatiate a new struct and store each seperated value as a part of said struct
		{
			Account account;
			accountFile2 >> account.username >> account.passcode >> account.chipBalance;
			accounts.push_back(account); // push the struct into the Vector - A vector is an array with a non specific storage limit
		}
		int logInAttempts = 0;
		int logInMax = 5;
		bool loopControl2 = true;
		while (loopControl2)
		{
			if (logInAttempts == logInMax) // if the user has too many attempts at password kick them out
			{
				cout << "You have been locked out for too many failed attempts try again later" << endl;
				loopControl = false;
				loopControl2 = false;
			}
			else
			{
				cout << "Please Enter your Username: \n";
				cin >> attemptedUsername; // enter user name
				attemptedPasscode = val.intValidation("Please Enter your Passcode:"); // enter passcode
				int z = 0;
				bool isCorrect = false;
				while (z < count)
				{
					if (attemptedUsername == accounts[z].username && attemptedPasscode == accounts[z].passcode) // if username and password are a match to anything in the vector log them in
					{
						cout << "Welcome to the casino {" << attemptedUsername << "}!" << endl;
						loopControl2 = false;
						loopControl = false;
						isCorrect = true;
						break;
					}
					else
					{
						z++; // if current struct isnt the right one in the vector go to the next one
					}
				}
				if (isCorrect == true) // if correct flag is true take user to the game
				{
					game.startGame(accounts[z].username, accounts[z].chipBalance, accounts[z].passcode, z);
				}
				else // if username or password incorrect, add to log in attempts and try again
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
	Validation val; // instatiate main menu, custom math, and validation
	ifstream accountFile("AccountInfo.txt"); // open account file
	int count = 0;
	if (accountFile.is_open()) // count lines of file
	{
		string line;
		while (!accountFile.eof())
		{
			getline(accountFile, line);
			count++;
		}
	}
	accountFile.close();
	ifstream accountFile2("AccountInfo.txt"); // reopen to reset
	std::vector<Account> preAccounts; // vector of struct again
	for (size_t i = 0; i < count; i++)
	{
		Account account; // instatiate struct
		accountFile2 >> account.username >> account.passcode >> account.chipBalance;
		preAccounts.push_back(account); // take info and store same as before
	}
	accountFile2.close();
	int const passcodeLenReq = 4; // pass code length must be 4 digits
	bool loopControl = true;
	cout << "Welcome to the account creation center!" << endl; // welcome message
	string newUsername;
	int newPasscode;
	while (loopControl)
	{
		int innerCount = count;
		cout << "The first step of creating an account is to choose a username!" << endl;
		cout << "Please enter a username: \n"; // new username
		cin >> newUsername;
		bool passCodeLoop = true;
		while (passCodeLoop)
		{
			newPasscode = val.intValidation("Please enter a new passcode! Your passcode must be 4 digits long:\n"); // enter a number
			int passcodeLen = cusMath.countDigit(newPasscode); // check if number is 4 digits long
			if (passcodeLen != passcodeLenReq) // if not it must be 4 long
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
			if (newUsername == preAccounts[i].username) // check is username is already in use. 
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
	int baseBalance = 25000; // starting balance is 25000
	ofstream fileOutput; 
	fileOutput.open("AccountInfo.txt", std::ios_base::app); // open text file in append mode to add to file but not rewrite
	fileOutput << "\n" << newUsername << " " << newPasscode << " " << baseBalance; // write to a clean new line
	cout << "Account created enjoy! Please log in with your details!" << endl;
	cout << "The program needs to shutdown to properly configure the account. Please restart the program and log in!" << endl;
}

void AccountSystem::SetBalance(int balanceChange, bool isWin, int playerBal, string playerUserName, int playerPassCode, int z) // function to set a new balance after playing a round
{
	if (isWin) // if player wins add winnings to balance
	{
		playerBal = playerBal + balanceChange;
	}
	else if (isWin == false) // if player loses take loseings from balance
	{
		playerBal = playerBal - balanceChange;
	}
	/*Line Counter and reader*/
	
	ifstream accountFile3("AccountInfo.txt");
	int count = 0;
	if (accountFile3.is_open())
	{
		string line;
		while (!accountFile3.eof()) // counts lines
		{
			getline(accountFile3, line);
			count++;
		}
	}
	accountFile3.close();

	ifstream accFile("AccountInfo.txt"); // stores data in a struct and vector
	std::vector<Account> accounts2;
	Account account2;
	for (size_t p = 0; p < count; p++)
	{
		Account account2;
		accFile >> account2.username >> account2.passcode >> account2.chipBalance;
		accounts2.push_back(account2);
	}
	accFile.close();
	ofstream accFileWrite;
	accFileWrite.open("AccountInfo.txt", std::ios_base::trunc); // open file in rewrite mode
	for (size_t i = 0; i < count; i++)
	{
		if (i == z) // if current line is old current users line
		{
			if (i == 0) // checks if the users data was stored on the top line
			{
				accFileWrite << playerUserName << " " << playerPassCode << " " << playerBal; // update new balance and all other data
			}
			else
			{
				accFileWrite << "\n" << playerUserName << " " << playerPassCode << " " << playerBal; // if it is not the top line of file add a new line
			}
			
		}
		else
		{
			if (i == 0) // if the current line isnt the users then rewrite all other data to file
			{
				accFileWrite << accounts2[i].username << " " << accounts2[i].passcode << " " << accounts2[i].chipBalance; // checks for top line for formmating
			}
			else
			{
				accFileWrite << "\n" << accounts2[i].username << " " << accounts2[i].passcode << " " << accounts2[i].chipBalance;
			}
		}
	}
	accFileWrite.close();
	cout << "File saving done" << endl; // file saving complete
}