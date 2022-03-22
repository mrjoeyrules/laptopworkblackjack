#pragma once
#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <string>
using namespace std;
class Game
{
private:
	void dealCards();
	void playRound();
	void defineDeck();
public:
	void startGame(string username, int chipBal);
};
#endif
