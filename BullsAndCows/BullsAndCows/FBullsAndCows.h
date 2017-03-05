#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowsCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EWordStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullsAndCows {
	int32 n = myWordLength;
public:
	FBullsAndCows(); // Constructor

	void Reset(); // TODO: Make a more rich return value.

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	void SetWordLength(int32);
	int32 GetWordLength() const;

	bool IsGameWon() const;
	EWordStatus CheckGuessValidity(FString) const; // TODO: Make a more rich return value.

	FBullCowsCount SubmitValidGuess(FString);

// ^^ Please try and ignore this and focuson the interaface above ^^
private:
	// See constructor for initialization
	int32 myCurrentTry;
	int32 myMaxTries;
	FString myHiddenWord;
	bool bGameIsWon;

	// for user
	int32 myWordLength = 3;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};