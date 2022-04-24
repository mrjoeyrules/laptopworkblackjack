#include <iostream>
#include <string>
#include <fstream>
#include "Validation.h"
#include "AccountSystem.h"
#include "MainMenu.h"
using namespace std;

// simple main menu system

void MainMenu::mainMenu()
{
    bool loopControl = true;
    int const maxChoices = 3;
    int menuChoices[maxChoices] = { 1,2,3 };
    Validation val; // instantiate validation class
    AccountSystem accSys; // instantiate account system class
    int menuChoice;
    cout << "Welcome to the Joey Casino! \nIn this casino we specialise in blackjack! \nPlease Log in or Create an Account\n" << endl; // welcome message
    while (loopControl)
    {
        menuChoice = val.intValidation("Pick an option please:\n1. Log In:\n2. Create an Account:\n3. Exit:\n"); // calls int validation becuse the user can only enter numbers
        if (menuChoice == menuChoices[0]) // if user enters 1
        {
			loopControl = false;
            accSys.LogIn(); // user goes to log in function
        }
        else if (menuChoice == menuChoices[1]) // if user enters 2
        {
            accSys.AccountCreator(); // user goes to account creation function
            loopControl = false;
        }
        else if (menuChoice == menuChoices[2])
        {
            loopControl = false; // breaks loop and code ends, ending the program
        }
        else
        {
            cout << "You must enter a number between " << menuChoices[0] << " and " << maxChoices << endl; // if the user enters a number that doesnt take them anywhere they get a warning message
        }
    }

}