#include "Game.h"
#include <iostream>
#include <string>
#include <vector>
#include "FileSystem.h"
#include "Validation.h"
#include "MainMenu.h"
#include <time.h>
using namespace std;

int playerCurrentCount = 0;
int dealerCurrentCount = 0;
int const MaxCardsPerDeck = 13;
int const MaxCardsPerDeckAce = 14;
int const MaxDecks = 4;
int const Maxsuits = 4;
int totalOfCardsDeck1 = 13;
int totalOfCardsDeck2 = 13;
int totalOfCardsDeck3 = 13;
int totalOfCardsDeck4 = 13;
int playerChipBal;
int cardValue[MaxCardsPerDeckAce] = { 1,2,3,4,5,6,7,8,9,10,10,10,10,11 };
string suits[Maxsuits] = { "Hearts", "Diamonds", "Clubs", "Spades" };
int currentSuit;
struct Decks
{
	std::vector<string> decks;
};

struct Returns
{
	int returnCard = 0;
	int returnDeck = 0;
};

Decks deckMaker[MaxDecks];

void Game::defineDeck()
{
	
	for (size_t i = 0; i < MaxDecks; i++)
	{
		 deckMaker[i].decks = { "A","2","3","4","5","6","7","8","9","10","J","Q","K" };
	}	
}

int Game::dealCards()
{
	srand(time(NULL));
	int cardValueInner;
	int currentDeck;
	bool loopControl = true;
	int randomDeck = 0;
	int randomCard = 0;
	int currentCard = 0;
	while (loopControl)
	{
		if (totalOfCardsDeck1 == 0)
		{
			randomDeck = rand() % 3 + 1;
			randomCard = rand() % totalOfCardsDeck1;
		}
		else if (totalOfCardsDeck2 == 0)
		{
			int possibleDecks[3] = { 0,2,3 };
			int partRandom = rand() % 2;
			randomDeck = possibleDecks[partRandom];
			randomCard = rand() % totalOfCardsDeck2;
		}
		else if (totalOfCardsDeck3 == 0)
		{
			int possibleDecks[3] = { 0,1,3 };
			int partRandom = rand() % 2;
			randomDeck = possibleDecks[partRandom];
			randomCard = rand() % totalOfCardsDeck3;
		}
		else if (totalOfCardsDeck4 == 0)
		{
			int possibleDecks[3] = { 0,1,2 };
			int partRandom = rand() % 2;
			randomDeck = possibleDecks[partRandom];
			randomCard = rand() % totalOfCardsDeck4;
		}
		else
		{
			randomDeck = rand() % 4;
			if (randomDeck == 0)
			{
				randomCard = rand() % totalOfCardsDeck1;
			}
			else if (randomDeck == 1)
			{
				randomCard = rand() % totalOfCardsDeck2;
			}
			else if (randomDeck == 2)
			{
				randomCard = rand() % totalOfCardsDeck3;
			}
			else if (randomDeck == 3)
			{
				randomCard = rand() % totalOfCardsDeck4;
			}
		}
		if (randomCard == 0)
		{
			if (playerCurrentCount < 11)
			{
				cardValueInner = cardValue[12];
				currentDeck = randomDeck;
				currentCard = randomCard;
				deckMaker[currentDeck].decks.erase(deckMaker[currentDeck].decks.begin()+currentCard - 1);
				if (currentDeck == 0)
				{
					totalOfCardsDeck1 -= 1;
				}
				else if (currentDeck == 1)
				{
					totalOfCardsDeck2 -= 1;
				}
				else if (currentDeck == 2)
				{
					totalOfCardsDeck3 -= 1;
				}
				else if (currentDeck == 3)
				{
					totalOfCardsDeck4 -= 1;
				}
				currentSuit = currentDeck;
				return cardValueInner + 1;
				loopControl = false;
			}
			else
			{
				cardValueInner = cardValue[randomCard];
				currentDeck = randomDeck;
				currentCard = randomCard;
				deckMaker[currentDeck].decks.erase(deckMaker[currentDeck].decks.begin() + currentCard - 1);
				if (currentDeck == 0)
				{
					totalOfCardsDeck1 -= 1;
				}
				else if (currentDeck == 1)
				{
					totalOfCardsDeck2 -= 1;
				}
				else if (currentDeck == 2)
				{
					totalOfCardsDeck3 -= 1;
				}
				else if (currentDeck == 3)
				{
					totalOfCardsDeck4 -= 1;
				}
				currentSuit = currentDeck;
				return cardValueInner + 1;
				loopControl = false;
			}
		}
		else
		{
			cardValueInner = cardValue[randomCard];
			currentDeck = randomDeck;
			currentCard = randomCard;
			deckMaker[currentDeck].decks.erase(deckMaker[currentDeck].decks.begin() + currentCard -1);
			if (currentDeck == 0)
			{
				totalOfCardsDeck1 -= 1;
			}
			else if (currentDeck == 1)
			{
				totalOfCardsDeck2 -= 1;
			}
			else if (currentDeck == 2)
			{
				totalOfCardsDeck3 -= 1;
			}
			else if (currentDeck == 3)
			{
				totalOfCardsDeck4 -= 1;
			}
			currentSuit = currentDeck;
			return cardValueInner + 1;
			loopControl = false;
		}

	}
	return 0;
}

void Game::playerRound()
{
	int currentPlayerCard = dealCards();
	int currentCardSuit = currentSuit;
	playerCurrentCount = cardValue[currentPlayerCard];
	string cardValueName = deckMaker[currentCardSuit].decks[currentPlayerCard];
	string currentSuit = suits[currentCardSuit];
	cout << "You have been dealt a " << cardValueName << " of " << currentSuit << endl;
	cout << "Your count is " << playerCurrentCount + 1 << endl;
}
void Game::dealerRound()
{
	int currentDealerCard = dealCards();
	currentDealerCard += 1;
	int currentCardSuit = currentSuit;
	dealerCurrentCount = cardValue[currentDealerCard];
	string cardValueName = deckMaker[currentCardSuit].decks[currentDealerCard];
	string currentSuit = suits[currentCardSuit];
	cout << "You have been dealt a " << cardValueName << " of " << currentSuit << endl;
	cout << "The Dealers count is " << dealerCurrentCount + 1 << endl;
}

void Game::playRound()
{
	Validation val;
	playerCurrentCount = 0;
	dealerCurrentCount = 0;
	int roundBet = 0;
	bool betValidation = true;
	while (betValidation)
	{
		roundBet = val.intValidation("Please enter your wager for this round of BlackJack: \n");
		if (roundBet > playerChipBal)
		{
			cout << "You cannot bet more chips than you have! You have " << playerChipBal << "chips!" << endl;
		}
		else
		{
			betValidation = false;
		}
	}
	playerRound();
	dealerRound();
}



void Game::reshuffleCards()
{
	totalOfCardsDeck1 = 13;
	totalOfCardsDeck2 = 13;
	totalOfCardsDeck3 = 13;
	totalOfCardsDeck4 = 13;
	defineDeck();
}

void Game::startGame(string username, int chipBal)
{
	string playerUserName;
	playerUserName = username;
	playerChipBal = chipBal;
	defineDeck();
	playRound();
}