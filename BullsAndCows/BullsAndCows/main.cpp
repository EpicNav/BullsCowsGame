// BullsAndCows.cpp : Defines the entry point32 for the console application.
/*This is the console executable, that makes use of the BullCow class
* This acts as the view in MVC pattern, and is responsible for all
* user interaction. For game logic see the FBullsAndCows class.
*/

#include "stdafx.h"
#include <iostream>
#include <string>
#include "FBullsAndCows.h"

using FText = std::string;
using int32 = int;

void printIntro();
FText printGuess();
void playGame();
bool AskToPlayAgain();
void printGameSummary();

FBullsAndCows BCGame; // initiate a new game

int main()
{
	// Calls the intro method / function
	bool bPlayAgain = false;
	do {
		printIntro();
		playGame();
		bPlayAgain = AskToPlayAgain();
	 } while (bPlayAgain);

	return 0;
}

void printIntro() {
	// int32roduction to game
	constexpr int32 WORD_LENGTH = 9;
	std::cout << "Welcome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << std::endl;
	std::cout << "              }   {         ___ " << std::endl;
	std::cout << "              (o o)        (o o) " << std::endl;
	std::cout << "   /----------\\ /          \\ /----------\\ " << std::endl;
	std::cout << "  / | Gursagar |O            O| Dilpreet | \\ " << std::endl;
	std::cout << " *  |-,------- |              |----------|  * " << std::endl;
	std::cout << "    ^          ^              ^          ^ " << std::endl;

	// START: Allowing user to select the word length
	int32 SelectWordLength;
	do {
		std::cout << "Please select the word length between 3 and 7: ";
		std::cin >> SelectWordLength;

		// Checking if word length is between the provided numbers
		if (SelectWordLength < 3) 
		{
			std::cout << "Word length too short" << std::endl;
		}
		else if (SelectWordLength > 7) {
			std::cout << "Word length too long" << std::endl;
		}

		// Setting the word length in FBullsAndCows with setter
		BCGame.SetWordLength(SelectWordLength);
	} while (SelectWordLength < 3 || SelectWordLength > 7);
	std::cout << "You selected the word length of " << BCGame.GetWordLength() << std::endl;
	// END: Allowing user to select the word length

	// Introduction continues
	std::cout << "Can you guess the " << BCGame.GetWordLength();
	std::cout << " letter isogram I'm thinking of? \n";
	std::cout << std::endl;
	return;
}

// Loop contunually until the user gives a valid guess
FText GetValidGuess() {
	EWordStatus Status = EWordStatus::Invalid_Status;
	FText guess;
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << " Enter your guess: ";
		std::getline(std::cin, guess);

		Status = BCGame.CheckGuessValidity(guess);
		switch (Status) {
		case EWordStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word." << std::endl << std::endl;
			break;
		case EWordStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters." << std::endl << std::endl;
			break;
		case EWordStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters." << std::endl << std::endl;
		default:
			// assume the guess is valid
			break;
		}
	} while (Status != EWordStatus::OK); // Keep looping till we get no errors
	return guess;
}

void playGame() {
	BCGame.Reset();
	int32 maxTries = BCGame.GetMaxTries();
	
	// loop asking for guesses while the game
	// is NOT won and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= maxTries) {
		FText guess = GetValidGuess();

		// Submit valid guess to the game, and receive counts
		FBullCowsCount BullCowCount = BCGame.SubmitValidGuess(guess);

		std::cout << "Bulls: " << BullCowCount.Bulls;
		std::cout << ". Cows: " << BullCowCount.Cows << std::endl;
	}

	printGameSummary();
	return;
}

void printGameSummary() {
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE - YOU WON" << std::endl;
	}
	else {
		std::cout << "Better luck next time" << std::endl;
	}
	return;
}

bool AskToPlayAgain() {
	std::cout << "Do you want to play agai with the same hidden word. (y/n)";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y' || Response[0] == 'Y');
}

// Extra methods

void AcceptUserLength(int32){}
