#include "Game.h"
#include <iostream>
#include <string>
#include <vector>
#include "FileSystem.h"
#include "Validation.h"
#include "MainMenu.h"
using namespace std;

int const MaxCardsPerDeck = 13;
int const MaxCardsPerDeckAce = 14;
int const MaxDecks = 4;

struct Decks
{
	string deck[MaxCardsPerDeck];
};

void Game::defineDeck()
{
	int cardValue[MaxCardsPerDeckAce] = { 1,2,3,4,5,6,7,8,9,10,10,10,11 };
	Decks deckMaker[MaxDecks];
	for (size_t i = 0; i < MaxDecks; i++)
	{
		deckMaker[i].deck = { "A","2","3","4","5","6","7","8","9","J","Q","K" }
	}
}