/* This is the console executable, that makes use  of the BullCow class 
This acts as the view in a MVC pattern, and is responsible for all 
user interaction. For game logic see the FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"
#include <stdlib.h>     /* srand, rand */

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
int32 main();
void PrintIntro ();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();
void SetGameDifficulty(); //NEW

FBullCowGame BCGame; //instantiate a new game, with we re-use across plays


	//The entry point for our application
	int main()
	{
		bool bPlayAgain = false;
		do
		{
			PrintIntro();
			SetGameDifficulty();//NEW
			PlayGame();
			bPlayAgain = AskToPlayAgain();
		} while (bPlayAgain);
		
		return 0; //exit the game
	}

void PrintIntro() 
{
	std::cout << "\n\nWelcome to Bulls and Cows game\n";

	std::cout << "   _____-----__/        ___----__          \n";
	std::cout << " _/    BULL  _`|   ,_,_/   COW   \\_       \n";
	std::cout << "' |___-_,_,/       |. _          | --*     \n";
	std::cout << "  //  ]} \\/        |_/ //\\---U-\\ /      \n";
	std::cout << " //   \\\\ \\\\            |[   ''  ||     \n";


	std::cout << "Can you guess the isogram I'm thinking off ? \n"; 
	return;
}


void SetGameDifficulty() // NEW
{
	BCGame.Reset();

	int32 difficulty = 0;
	std::cout << "So please tell me how much letters do you like on it from 3 to 7: ";
	std::cin >> difficulty;
	std::cout << std::endl;

	EDifficultyStatus DifficultyStatus = EDifficultyStatus::Invalid_Status;
	//if (!EDifficultyStatus::Ok)
	//{
		DifficultyStatus = BCGame.CheckDifficultyValidity(difficulty);
		do {
			switch (DifficultyStatus)
			{
				case EDifficultyStatus::Not_Number:
					std::cout << "Please enter a number try again: ";
					std::cin >> difficulty;
					break;
				case EDifficultyStatus::Invalid_Value:
					std::cout << "Please enter a number from 3 to 7: ";
					std::cin >> difficulty;
			default:
				break;
			}
			

		} while (DifficultyStatus != EDifficultyStatus::Ok); // keep looping until we get no errors
	//}

	BCGame.ChooseHiddenWord(difficulty);

	std::cout << std::endl;
	std::cout << "Good choice, so you will guess a " << difficulty;
	std::cout << " letters isogram\n\n";
	std::cout << " LET'S START !\n\n\n";

	return;
}


// Playes a single game a to completion
void PlayGame()
{
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game
	// is NOT won and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();

		// submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}


// loop continually until the user gives a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::cin.ignore(); // ignores all before this getline
		std::getline(std::cin, Guess); 

		// check status and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLenght() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word witout repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word (y/n) ? ";
	FText Response = "";
	std::getline(std::cin, Response);
	std::cout << std::endl;
	std::cout << "____________________________________________________________";
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE - YOU WIN !\n";
	}
	else 
	{
		std::cout << "Better luck next time\n";
	}
}



