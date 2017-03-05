#include "stdafx.h"
#include "FBullsAndCows.h"
#include <map>
#include <array>
#include <algorithm>
#define TMap std::map

FBullsAndCows::FBullsAndCows() // default constructor
{
	Reset();
}

void FBullsAndCows::Reset()
{
	const std::array<FString, 5> HIDDEN_WORDS_LIST = { "pen", "card", "crest", "planet", "warship" };
	int32 n = myWordLength;
	auto find = std::find_if(HIDDEN_WORDS_LIST.begin(), HIDDEN_WORDS_LIST.end(), [&n](const std::string& str) { return str.size() == n; });
	FString Word = *find;

	myHiddenWord = Word;

	myCurrentTry = 1;
	bGameIsWon = false;
	return;
}

int32 FBullsAndCows::GetMaxTries() const {
	TMap<int32, int32> WordLengthToMaxTries{ { 3, 5 }, { 4, 5 }, { 5, 4 }, { 6, 3 }, { 7, 4 } };
	return WordLengthToMaxTries[myHiddenWord.length()];
}
int32 FBullsAndCows::GetCurrentTry() const { return myCurrentTry; }
int32 FBullsAndCows::GetHiddenWordLength() const { return myHiddenWord.length(); }
void FBullsAndCows::SetWordLength(int32 WordLength)
{
	myWordLength = WordLength;
}
int32 FBullsAndCows::GetWordLength() const
{
	return myWordLength;
}
bool FBullsAndCows::IsGameWon() const{ return bGameIsWon; }

EWordStatus FBullsAndCows::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) {
		return EWordStatus::Not_Isogram; // TODO: Write function
	}
	else if (!IsLowercase(Guess)) {
		return EWordStatus::Not_Lowercase; // TODO: Write function
	}
	else if (Guess.length() != GetHiddenWordLength()) {
		return EWordStatus::Wrong_Length;
	}
	else {
		return EWordStatus::OK;
	}
}

// receives a VALID guess, increment turns, and returns count
FBullCowsCount FBullsAndCows::SubmitValidGuess(FString Guess)
{
	myCurrentTry++;
	FBullCowsCount BullCowCount;
	int32 WordLength = myHiddenWord.length(); // assuming same length as guess

	// loop through all letters in the hidden word
	for (int32 i = 0; i < WordLength; i++) {
		// compare letters against the guess
		for (int32 j = 0; j < WordLength; j++) {
			if (Guess[j] == myHiddenWord[i]) {
				if (i == j) { // if they are in the same place
					BullCowCount.Bulls++; // increment bulls
				}
				else {
					BullCowCount.Cows++; // must be a cow
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	} else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

// PRIVATE METHODS

bool FBullsAndCows::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen; // setup our map
	for (auto Letter : Word)   // for all letters of the word
	{
		Letter = tolower(Letter); // handle mixed case
		// if the letter is in the map
		if (LetterSeen[Letter])
		{
			return false; // we do NOT have an isogram
		}
		else {
			LetterSeen[Letter] = true; // add the letter to the map as seen
		}
	}
	return true; // for example in cases where /0 is entered
}

bool FBullsAndCows::IsLowercase(FString Word) const
{
	for (auto Letter : Word) {
		// if NOT a lowercase letter
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}
