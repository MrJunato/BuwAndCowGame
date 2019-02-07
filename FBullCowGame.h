/* The game logic (no view code or direct user interaction)
The game is a simples guess the word game based on Mastermind
*/

#pragma once
#include <string>

// to make syntax Unreal frinedly
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

enum EDifficultyStatus
{
	Invalid_Status,
	Not_Number,
	Invalid_Value,
	Ok
};


class FBullCowGame {
public:
	FBullCowGame(); //Constructor

	//Getters
	int32 GetMaxTries()const;
	int32 GetCurrentTry()const;
	int32 GetHiddenWordLenght()const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;
	EDifficultyStatus CheckDifficultyValidity (int32); //NEW
	void ChooseHiddenWord(int32); //NEW
	

	void Reset(); 
	FBullCowCount SubmitValidGuess(FString);

private:
	//See constructor for initialisation
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;
	int32 NumberOfHiddenWords; //NEW
	int32 difficulty;//NEW

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
	bool IsValidLenght(int32) const; //NEW
};
