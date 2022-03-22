#include "Game.h"
#include <iostream>
#include <string>
#include <vector>
#include "FileSystem.h"
#include "Validation.h"
#include "MainMenu.h"
using namespace std;

int playerCurrentCount = 0;
int dealerCurrentCount = 0;
int const MaxCardsPerDeck = 13;
int const MaxCardsPerDeckAce = 14;
int const MaxDecks = 4;
string playerUserName;
int playerChipBal;
int cardValue[MaxCardsPerDeckAce] = { 1,2,3,4,5,6,7,8,9,10,10,10,11 };
struct Decks
{
	std::vector<string> decks;
};

Decks deckMaker[MaxDecks];

void Game::defineDeck()
{
	
	for (size_t i = 0; i < MaxDecks; i++)
	{
		 deckMaker[i].decks = { "A","2","3","4","5","6","7","8","9","J","Q","K" };
	}	
}

void Game::dealCards()
{
	bool loopControl = true;
	int randomDeck = 0;
	int cardValueInner;
	int randomCard = 0;
	while (loopControl)
	{
		randomDeck = rand() % 4;
		randomCard = rand() % 12;
		if (randomCard == 0)
		{
			if (playerCurrentCount < 11)
			{
				cardValueInner = cardValue[12];
			}
			else
			{
				cardValueInner = cardValue[randomCard];
			}
		}
		else
		{
			cardValueInner = cardValue[randomCard];
		}

	}
	
}

void Game::playRound()
{

}

void Game::startGame(string username, int chipBal)
{
	playerUserName = username;
	playerChipBal = chipBal;
	defineDeck();
}