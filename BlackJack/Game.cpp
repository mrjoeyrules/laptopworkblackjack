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
int cardCount = 0;
struct Decks
{
	std::vector<string> decks;
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
	srand(time(0));
	int cardValueInner = 0;
	int currentDeck = 0;
	bool loopControl = true;
	int randomDeck = 0;
	int randomCard = 0;
	int currentCard = 0;
	while (loopControl)
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
		cardValueInner = cardValue[randomCard + 1];
		currentDeck = randomDeck;
		currentCard = randomCard;
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
		return cardValueInner;
		loopControl = false;
	}
	return 0;
}
int Game::playerDecision()
{
	bool loopControl = true;
	Validation validation;
	while (loopControl)
	{
		cout << "You currently have a " << playerCurrentCount << " do you want to hit or stick?" << endl;
		int decision = validation.intValidation("Press 1: To Hit, Press 2: To Stick \n");
		if (decision == 1)
		{
			loopControl = false;
			return 1;
		}
		else if (decision == 2)
		{
			loopControl = false;
			return 2;
		}
		else
		{
			cout << "Please enter either 1, or 2!" << endl;
		}
	}
}
int Game::playerDecisionDouble()
{
	bool loopControl = true;
	Validation validation;
	while (loopControl)
	{
		cout << "You currently have a " << playerCurrentCount << " do you want to hit or stick or Double Down?" << endl;
		int decision = validation.intValidation("Press 1: To Hit, Press 2: To Stick, Press 3: To Double Down \n");
		if (decision == 1)
		{
			loopControl = false;
			return 1;
		}
		else if (decision == 2)
		{
			loopControl = false;
			return 2;
		}
		else if (decision == 3)
		{
			loopControl = false;
			return 3;
		}
		else
		{
			cout << "Please enter either 1, 2, or 3!" << endl;
		}
	}
}

void Game::playerRound()
{
	int currentPlayerCard = 0;
	currentPlayerCard = dealCards();
	int currentCardSuit = 0;
	currentCardSuit = currentSuit;
	playerCurrentCount += cardValue[currentPlayerCard];
	string cardValueName = deckMaker[currentCardSuit].decks[currentPlayerCard];
	string currentSuit = suits[currentCardSuit];
	cout << "You have been dealt a " << cardValueName << " of " << currentSuit << endl;
	cout << "Your count is " << playerCurrentCount<< endl;
}
void Game::dealerRound()
{
	int currentDealerCard = dealCards();
	int currentCardSuit = currentSuit;
	dealerCurrentCount += cardValue[currentDealerCard];
	string cardValueName = deckMaker[currentCardSuit].decks[currentDealerCard];
	string currentSuit = suits[currentCardSuit];
	cout << "You have been dealt a " << cardValueName << " of " << currentSuit << endl;
	cout << "The Dealers count is " << dealerCurrentCount << endl;
}


void Game::playRound()
{
	bool isStuck = false;
	bool bust = false;
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
	for (size_t i = 0; i < 2; i++)
	{
		playerRound();
		dealerRound();
	}
	int playerDecisionReturnFirst = playerDecisionDouble();
	while (isStuck != true)
	{
		if (playerCurrentCount > 21)
		{
			cout << "You have gone bust" << endl;
			isStuck = true;
			bust = true;
		}
		else
		{
			if (playerDecisionReturnFirst == 1)
			{
				playerRound();
				int playerDecisionReturn = playerDecision();
				if (playerDecisionReturn == 1)
				{
					playerRound();

				}
				else if (playerDecisionReturn == 2)
				{
					isStuck = true;
				}
			}
			else if (playerDecisionReturnFirst == 2)
			{
				cout << "You have stuck at " << playerCurrentCount << endl;
				isStuck = false;
			}
			else if (playerDecisionReturnFirst == 3)
			{
				roundBet *= 2;
				playerRound();
				isStuck = true;
			}
		}
		
	}
	if (bust)
	{
		cout << "You have busted at " << playerCurrentCount << endl;
	}
	cout << "You have stuck at " << playerCurrentCount << endl;
	
}

void Game::dealerPlayRound()
{
	
	bool dealerStuck = false;
	while (dealerStuck != true)
	{
		if (dealerCurrentCount >= 17)
		{
			dealerStuck = true;
			if (dealerCurrentCount > 21)
			{
				cout << "Dealer is Bust" << endl;
			}
		}
		else
		{
			dealerRound();
		}
	}
	
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