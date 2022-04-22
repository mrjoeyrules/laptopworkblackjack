#include <iostream>
#include <string>
#include "Validation.h"
using namespace std;

/*A function that validates and input as a int and returns the validated input*/
int Validation::intValidation(string inputMessage)
{
    bool loopControl = true;
    while (loopControl)
    {
        string rawValue; // Raw Value being entered by user
        cout << inputMessage << endl;
        cin >> rawValue; // input
        try // trys following code
        {
            int convertedValue;
            convertedValue = stoi(rawValue); // converted raw value into new int variable
            loopControl = false; // if succedes breaks loop
            return convertedValue; // returns value
        }
        catch (const std::exception&) // if error occurs output statement
        {
            cout << "You must enter a whole number, Try Again" << endl;
        }
    }
}
