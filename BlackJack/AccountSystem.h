#pragma once
#ifndef AccountSystem_H
#define AccountSystem_H
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "AccountSystem.h"
#include "Validation.h"
#include "CustomMath.h"
#include "MainMenu.h"
#include "Game.h"
using namespace std;
class AccountSystem
{
public:
    void LogIn();
    void AccountCreator();
    void SetBalance(int balanceChange, bool isWin, int playerBal, string playerUserName, int playerPassCode);
};
#endif