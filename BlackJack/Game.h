#pragma once
#ifndef GAME_H
#define GAME_H
#include "Game.h"
#include <iostream>
#include <string>
#include <vector>
#include "FileSystem.h"
#include "Validation.h"
#include "MainMenu.h"
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
	void dealerPlayRound();
public:
	void startGame(string username, int chipBal);
};
#endif
