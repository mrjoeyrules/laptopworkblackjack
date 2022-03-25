#pragma once
#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <string>
using namespace std;
class Game
{
private:
	int dealCards(int* cardValueInner, int* currentDeck);
	void playRound();
	void reshuffleCards();
	void defineDeck();
public:
	void startGame(string username, int chipBal);
};
#endif
