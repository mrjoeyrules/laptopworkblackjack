#pragma once
#ifndef GAME_H
#define GAME_H
#include "Game.h"
#include <iostream>
#include <string>
#include <vector>
#include "Validation.h"
#include "MainMenu.h"
#include <time.h>
#include <ctime>
#include <Windows.h>
#include "AccountSystem.h"
using namespace std;
class Game
{
private:
	int dealCards();
	void playRound();
	void reshuffleCards();
	void defineDeck();
	void playerRound();
	void dealerRound();
	int playerDecision();
	int playerDecisionDouble();
	void winningLogic(bool isBustPlayer, bool isBustDealer, int betAmount, bool isBlackJack, bool isDealerBlackJack, bool isDoubleDown);
	void dealerPlayRound(bool isBustPlayer, int betAmount, bool isBlackJack, bool isDoubleDown);
	void newRound();
public:
	void startGame(string username, int chipBal, int passCode, int z);
};
#endif