#pragma once
#ifndef AccountSystem_H
#define AccountSystem_H
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
class AccountSystem
{
public:
    void LogIn();
    void AccountCreator();
};
#endif