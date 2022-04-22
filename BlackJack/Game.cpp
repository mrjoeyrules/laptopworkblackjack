#include "Game.h"
#include <iostream>
#include <string>
#include <vector>
#include "Validation.h"
#include "MainMenu.h"
#include <time.h>
#include <Windows.h>
#include "AccountSystem.h"
using namespace std;

int playerPassCode = 0000;
int playerCurrentCount = 0;
int dealerCurrentCount = 0;
int const MaxCardsPerDeck = 13;
int const MaxCardsPerDeckAce = 14;
int const MaxDecks = 4;
int const Maxsuits = 4;
int totalOfCardsDeck1 = 14;
int totalOfCardsDeck2 = 14; // variables that are needed in most functions
int totalOfCardsDeck3 = 14;
int totalOfCardsDeck4 = 14;
int playerChipBal = 0;
int cardValue[MaxCardsPerDeckAce] = { 1,2,3,4,5,6,7,8,9,10,10,10,10,11 };
string suits[Maxsuits] = { "Hearts", "Diamonds", "Clubs", "Spades" };
int currentSuit;
int cardCount = 0;
string playerUserName;

// struct of decks

struct Decks
{
	std::vector<string> decks;
};


Decks deckMaker[MaxDecks]; // struct of an array

void Game::defineDeck()
{
	
	for (size_t i = 0; i < MaxDecks; i++)
	{
		 deckMaker[i].decks = { "A","2","3","4","5","6","7","8","9","10","J","Q","K" }; // all possible cards in a suit - 4 made in total
	}	
}

void Game::newRound() // function to decide to start a new round or end game
{
	int againAns = 0;
	bool againControl = true;
	Validation newVal; // instantiate validation
	while (againControl)
	{
		againAns = newVal.intValidation("Do you want to play another round. 1: Yes, 2: No\n"); // yes or no
		if (againAns == 1) // if play again
		{
			againControl = false;
			reshuffleCards(); // reshuffle the cards
			playRound(); // play again
		}
		else if (againAns == 2) // if not, cya 
		{
			cout << "Logging You out of the casino, Good night!\n" << endl;
			againControl = false;
		}
		else
		{
			cout << "Enter a number between 1 and 2!\n" << endl; // please just enter 1 or 2
		}

	}
}

int Game::dealCards()
{
	Validation validate; // instatiate validation
	srand(time(0));
	int cardValueInner = 0;
	int currentDeck = 0;
	bool loopControl = true;
	int randomDeck = 0;
	int randomCard = 0;
	while (loopControl)
	{
		randomDeck = rand() % 4; // picks a random deck
		if (randomDeck == 0)
		{
			randomCard = rand() % totalOfCardsDeck1; // makes sure to only randomise from the amount of cards available in this deck
			cardValueInner = cardValue[randomCard + 1]; // stores the value of the card
		}
		else if (randomDeck == 1)
		{
			randomCard = rand() % totalOfCardsDeck2;
			cardValueInner = cardValue[randomCard + 1];
		}
		else if (randomDeck == 2)
		{
			randomCard = rand() % totalOfCardsDeck3;
			cardValueInner = cardValue[randomCard + 1];
		}
		else if (randomDeck == 3)
		{
			randomCard = rand() % totalOfCardsDeck4;
			cardValueInner = cardValue[randomCard + 1];
		}
		if (randomCard == 0) // if the card is an ace
		{
			bool aceCheck = true;
			while (aceCheck)
			{
				int aceChoice = 0;
				aceChoice = validate.intValidation("You have drawn an ace do you want it to be worth 1: 11 or 2: 1? \n"); // do you want the ace to be an 11 or 1
				if (aceChoice == 1)
				{
					cardValueInner = cardValue[13];
					aceCheck = false;
				}
				else if (aceChoice == 2)
				{
					cardValueInner = cardValue[0];
					aceCheck = false;
				}
				else
				{
					cout << "You need to enter a number between 1 and 2!\n" << endl;
				}
			}
		}
		else
		{
			currentDeck = randomDeck; // takes away 1 card from the total of what ever take was chosen
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
			currentSuit = currentDeck; // stores the suit number
			return cardValueInner; // returns card value for maths
			loopControl = false;
		}
	}
	return 0;
}
int Game::playerDecision() // simple choice of hit or stick
{
	bool loopControl = true;
	Validation validation; // instatiate validation class
	while (loopControl)
	{
		cout << "You currently have a " << playerCurrentCount << " do you want to hit or stick? \n" << endl; // shows player there count 
		int decision = validation.intValidation("Press 1: To Hit, Press 2: To Stick \n"); // asks to hit or stick
		if (decision == 1)
		{
			loopControl = false;
			return 1; // returns choice
		}
		else if (decision == 2)
		{
			loopControl = false;
			return 2;
		}
		else
		{
			cout << "Please enter either 1, or 2! \n" << endl;
		}
	}
}
void Game::winningLogic(bool isBustPlayer, bool isBustDealer, int betAmount, bool isBlackJack, bool isDealerBlackJack, bool isDoubleDown) // decides outcome of game loss or win
{
	AccountSystem accSys; // instatiates account system class
	bool isWin = false;
	int playerWinnings = 0;
	int playerLosings = 0;
	if (isBlackJack) // if a blackjack is made 2 to 1 odds are won 
	{
		isWin = true; // sets win flag to true to make sure to add the winnings to total
		playerWinnings = betAmount * 2.5;
		accSys.SetBalance(playerWinnings, isWin, playerChipBal, playerUserName, playerPassCode); // calls function to set balance of user
	}
	else if (isDoubleDown) // if the user doubled down
	{
		if (playerCurrentCount > dealerCurrentCount && isBustPlayer == false) // if player won
		{
			isWin = true;
			cout << "You have won a double down Congratulations! \n" << endl;
			playerWinnings = betAmount * 2; // doubles winnings
			accSys.SetBalance(playerLosings, isWin, playerChipBal, playerUserName, playerPassCode);
			newRound(); // starts a new round
		}
		else if (dealerCurrentCount > playerCurrentCount && isBustDealer) // if dealer won
		{
			cout << "You have lost a double down Too Bad! \n" << endl;
			playerLosings = betAmount; // loses entire bet as bet is set to double earlier
			accSys.SetBalance(playerLosings, isWin, playerChipBal, playerUserName, playerPassCode);
			newRound();
		}
		else if (dealerCurrentCount == playerCurrentCount) // if the cards are the same player keeps bet
		{
			cout << "You and the dealer push, You keep your chips \n" << endl;
			newRound();
		}
		else if (isBustPlayer) // if player busts
		{
			cout << "You have lost via a bust\n" << endl;
			playerLosings = betAmount;
			accSys.SetBalance(playerLosings, isWin, playerChipBal, playerUserName, playerPassCode);
			newRound();
		}
		else if (isBustDealer) // if dealer busts
		{
			cout << "You have won via the dealer going bust\n" << endl;
			playerWinnings = betAmount;
			accSys.SetBalance(playerLosings, isWin, playerChipBal, playerUserName, playerPassCode);
			newRound();
		}
	}
	else if (playerCurrentCount > dealerCurrentCount && isBustPlayer == false) // if double down doesnt happen these occur, If player beats dealer and isnt bust then
	{
		isWin = true;
		playerWinnings = betAmount * 2; // player gets double the bet
		cout << "Player has won!\nYou have won " << playerWinnings << " chips congratulations" << "\n" << endl;
		accSys.SetBalance(playerLosings, isWin, playerChipBal, playerUserName, playerPassCode);
		newRound();
	}
	else if (playerCurrentCount < dealerCurrentCount && isBustPlayer == false && isBustDealer == false) // if the dealer wins and no ones bust
	{
		playerLosings = betAmount; // losing is the bet amount
		cout << "The dealer has beat you!\n" << endl;
		accSys.SetBalance(playerLosings, isWin, playerChipBal, playerUserName, playerPassCode);
		newRound();
	}
	else if (dealerCurrentCount == playerCurrentCount) // if cards are the same you push dont lose anything
	{
		cout << "You and the dealer push, You keep your chips \n" << endl;
		newRound();
	}
	else if (isBustPlayer) // if player busts
	{
		cout << "You have lost via a bust\n" << endl;
		playerLosings = betAmount;
		accSys.SetBalance(playerLosings, isWin, playerChipBal, playerUserName, playerPassCode);
		newRound();
	}
	else if (isBustDealer) // if dealer busts
	{
		cout << "You have won via the dealer going bust\n" << endl;
		playerWinnings = betAmount;
		accSys.SetBalance(playerLosings, isWin, playerChipBal, playerUserName, playerPassCode);
		newRound();
	}
}
int Game::playerDecisionDouble() // a simple decision like before but for if the player wants to doubledown, this only occurs on the first hit or stick after the first two cards are dealt
{
	bool loopControl = true;
	Validation validation;
	while (loopControl)
	{
		cout << "You currently have a " << playerCurrentCount << " do you want to hit or stick or Double Down? \n" << endl;
		int decision = validation.intValidation("Press 1: To Hit, Press 2: To Stick, Press 3: To Double Down \n"); // 3 option choice 
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
			cout << "Please enter either 1, 2, or 3! \n" << endl; // enter one of the numbers
		}
	}
}

void Game::playerRound() // deals the cards to the player and tells them what they have
{
	int currentPlayerCard = 0;
	currentPlayerCard = dealCards(); // deals the cards
	int currentCardSuit = 0;
	currentCardSuit = currentSuit;
	playerCurrentCount += cardValue[currentPlayerCard]; // adds to players count
	string cardValueName = deckMaker[currentCardSuit].decks[currentPlayerCard]; //cards value in text form
	string currentSuit = suits[currentCardSuit]; // cards suit in text form
	
	cout << "You have been dealt a " << cardValueName << " of " << currentSuit << "\n" << endl;
	Sleep(2000); // slows the outputs by 2 seconds to allow for better astetics
	cout << "Your count is " << playerCurrentCount << "\n" << endl;
	Sleep(2000);
}
void Game::dealerRound() // same as player round but for dealers cards
{
	int currentDealerCard = dealCards();
	int currentCardSuit = currentSuit;
	dealerCurrentCount += cardValue[currentDealerCard];
	string cardValueName = deckMaker[currentCardSuit].decks[currentDealerCard];
	string currentSuit = suits[currentCardSuit];

	cout << "The dealer has been dealt a " << cardValueName << " of " << currentSuit << "\n" << endl; // changed output message a little bit
	Sleep(2000);
	cout << "The Dealers count is " << dealerCurrentCount << "\n" << endl;
	Sleep(2000);
}



void Game::dealerPlayRound(bool isBustPlayer, int betAmount, bool isBlackJack, bool isDoubleDown) // logic for dealers turn
{
	bool isBustDealer = false;
	bool dealerStuck = false;
	bool isDealerBlackJack = false;
	if (dealerCurrentCount == 21) // if the dealer black jacks GG
	{
		isDealerBlackJack = true;
		winningLogic(isBustPlayer, isBustDealer, betAmount, isBlackJack, isDealerBlackJack, isDoubleDown);
	}
	else if (isBlackJack) // is player blackjacks, dealers turn ends
	{
		winningLogic(isBustPlayer, isBustDealer, betAmount, isBlackJack, isDealerBlackJack, isDoubleDown);
	}
	while (dealerStuck != true) // while not stuck
	{
		if (isBustPlayer)// if player is bust the dealer stick because they win no matter what
		{
			dealerStuck = true;
			cout << "The dealer has stuck at " << dealerCurrentCount << "\n" << endl;
			winningLogic(isBustPlayer, isBustDealer, betAmount, isBlackJack, isDealerBlackJack, isDoubleDown);
		}
		else if (dealerCurrentCount >= 17) // if the dealer gets a 17 or above they must stick
		{
			dealerStuck = true;
			if (dealerCurrentCount > 21) // if dealer goes above 21 they bust
			{
				isBustDealer = true;
				cout << "Dealer is Bust" << "\n" << endl;
				winningLogic(isBustPlayer, isBustDealer, betAmount, isBlackJack, isDealerBlackJack, isDoubleDown);
			}
			else // otherwise they stick
			{
				cout << "Dealer has stuck at " << dealerCurrentCount << "\n" << endl;
				winningLogic(isBustPlayer, isBustDealer, betAmount, isBlackJack, isDealerBlackJack, isDoubleDown);
			}
		}
		else // if not above 17 or on 17 they draw
		{
			dealerRound();
		}
	}
}

void Game::playRound() // starts the players turns and game
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
		cout << "You have " << playerChipBal << " chips\n" << endl; // informs player on chip balance
		roundBet = val.intValidation("Please enter your wager for this round of BlackJack: \n"); // asks for wager
		if (roundBet > playerChipBal) // you cannot bet more than you have
		{
			cout << "You cannot bet more chips than you have! You have " << playerChipBal << "chips!\n" << endl;
		}
		else
		{
			betValidation = false;
		}
	}
	for (size_t i = 0; i < 2; i++) // make sure both dealer and player draw two cards no matter what
	{
		playerRound();
		dealerRound();
	}
	int playerDecisionReturnFirst = playerDecisionDouble(); // double down question
	bool isDoubleDown = false;
	bool isBlackJack = false;
	if (playerCurrentCount == 21) // if 21 on default draw, thats a blackjack
	{
		isBlackJack = true;
		isStuck = true;
		cout << "Congratulations you got a black jack\n" << endl; // auto sticks and blackjack flag is active
	}
	else
	{
		if (playerCurrentCount > 21) // if you go over 21 you bust
		{
			bust = true;
			isStuck = true; // sticks and bust flag is active
			cout << "You have gone Bust\n" << endl;
		}
		else
		{
			while (isStuck != true) // while not stuck
			{

				if (playerDecisionReturnFirst == 1) // if on the double down questions you answered hit
				{
					playerRound(); // you draw
					if (playerCurrentCount > 21) // if you go over 21 you bust
					{
						bust = true;
						isStuck = true;
						cout << "You have gone Bust" << endl;
					}
					else
					{
						int playerDecisionReturn = playerDecision(); // if not you play normally
						if (playerDecisionReturn == 1) // hit = draw
						{
							playerRound();

						}
						else if (playerDecisionReturn == 2) // stick = stick
						{
							isStuck = true;
						}
					}
				}
				else if (playerDecisionReturnFirst == 2) // if you stick straight from default draw you stick
				{
					isStuck = true;
				}
				else if (playerDecisionReturnFirst == 3) // if you double down
				{
					if (roundBet * 2 > playerChipBal) // chcek you can double down
					{
						cout << "You do not have enough chips to double down!\n" << endl; // not enough chips brother
						playerDecisionReturnFirst = playerDecisionDouble(); // back to beginning, try again
					}
					else
					{
						roundBet *= 2; // double the round bet
						playerRound(); // one draw
						isStuck = true; // instant stuck
					}
				}
			}
			if (bust) // if bust is active youbust
			{
				cout << "You have busted at " << playerCurrentCount << "\n" << endl;
				dealerPlayRound(bust, roundBet, isBlackJack, isDoubleDown);
			}
			else // if not active you have stuck
			{
				cout << "You have stuck at " << playerCurrentCount << "\n" << endl;
				dealerPlayRound(bust, roundBet, isBlackJack, isDoubleDown);
			}
		}
	}
	cout << "You have stuck at " << playerCurrentCount << "\n" << endl; // you blackjack if down here :)
	dealerPlayRound(bust, roundBet, isBlackJack, isDoubleDown);
}

void Game::reshuffleCards() // reshuffle the cards, all cards are back in the deck
{
	totalOfCardsDeck1 = 13;
	totalOfCardsDeck2 = 13;
	totalOfCardsDeck3 = 13;
	totalOfCardsDeck4 = 13;
	defineDeck();
}

void Game::startGame(string username, int chipBal, int passCode) // starts the game, the only public function here
{
	playerPassCode = passCode; // takes info from account system for passing later
	playerUserName = username;
	playerChipBal = chipBal;
	defineDeck(); // defines the deck
	playRound(); // plays the round
}