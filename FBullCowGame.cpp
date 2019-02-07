#pragma once

#include "FBullCowGame.h"
#include <map>
#include <stdlib.h>     /* srand, rand */ //NEW
#include <algorithm> // to use std::sort(std::begin(v), std::end(v));

// to make syntax Unreal frinedly
#define TMap std::map 
using int32 = int;

FBullCowGame::FBullCowGame(){ Reset();}// default constructor

int32 FBullCowGame::GetCurrentTry()const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLenght()const { return MyHiddenWord.length();}
bool FBullCowGame::IsGameWon() const { return bGameIsWon;}

int32 FBullCowGame::GetMaxTries()const 
{ 
	TMap<int32, int32> WordLenghtToMaxTries{ {3,5},{4,7},{5,10},{6,14},{7,20}};
	return WordLenghtToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::ChooseHiddenWord(int32 difficulty) //NEW
{
	FString HiddenWordList[]{ "ant","cube","plane","planet","planets" };

	int32 count;
	int32 const HiddenWordListSize = sizeof(HiddenWordList) / sizeof(HiddenWordList[0]); // take the number of words in HiddenWordList 
	NumberOfHiddenWords = HiddenWordListSize;

	FString RightLetterNumberWords[HiddenWordListSize]; // It's an array that lists the words in LastWordOfList that have the choosen number of letters

	// Loop to found the words in the list that have the right number of letters according to difficulty
	for ( count = 0; count <= HiddenWordListSize; count++)
	{
		// If the word of the list has the number of letters equal to the difficulty number, than the code create a new list that has only right lenght words
		if (HiddenWordList[count].length() == difficulty)
		{
			MyHiddenWord = HiddenWordList[count];
		}
	}
	
	return;
}

void FBullCowGame::Reset() 
{
	//const FString HIDDEN_WORD = "planet"; // This must be an isogram //NEW
   //MyHiddenWord = HIDDEN_WORD;  //NEW
	MyHiddenWord = "";
	difficulty = 0; //NEW

	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) // if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLenght()) // if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

EDifficultyStatus FBullCowGame::CheckDifficultyValidity(int32 difficulty) //NEW
{
	//test if difficulty is a number
	int32 difficultyValidity = difficulty - difficulty;
	if (int32(difficulty) != difficulty)
	{
		return EDifficultyStatus::Not_Number;
	}
	else if (!IsValidLenght(difficulty))
	{
		return EDifficultyStatus::Invalid_Value;
	}
	else
	{
		return EDifficultyStatus::Ok;
	}
}


// receives a VALID guess, incriments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same lenght as guess

	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		// compare letters against all the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) {// if they're in the same place
					BullCowCount.Bulls++;//incriment bulls
				}
			    else {
					BullCowCount.Cows++;//must be a cow
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;// setup our map
	for (auto Letter : Word) // for all letters of the word
	{
		Letter = tolower(Letter); // handle mixed case 

		if (LetterSeen[Letter]) {// if the letter in the map 
			return false; // we do NOT have an isogram
		}
		else {
			LetterSeen[Letter] = true;// add the letter to the map as seen
		}
	}
	return true;// for example in cases where \0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter)) // if not a lowercase letter
		{
			return false;
		}
	}
	return true;
}

bool FBullCowGame::IsValidLenght(int32 difficulty) const
{
	if (difficulty <= NumberOfHiddenWords || difficulty >= 3)
	return true;
}


