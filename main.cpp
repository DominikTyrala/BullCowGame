//============================================================================
// Name        : BullCowGame.cpp
// Author      : Dominik Tyrala
// Version     : 0.1
// Copyright   : Your copyright notice
// Description : BullCowGame C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;

int main() {

	bool bPlayAgain = false;

	do{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	}while(bPlayAgain);

	return 0;
}

void PrintIntro(){
	std::cout << "Welcome to the Bull and Cow Game" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter word I am thinking of?" << std::endl;
	std::cout << std::endl;

	return;
}

void PlayGame(){
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	while(!BCGame.IsGameWon() && BCGame.GetMaxTries() <= MaxTries){
		FText Guess = GetValidGuess();

		//submit guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
}

FText GetValidGuess(){
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do{
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout<<"Try " << CurrentTry <<". Enter your guess: ";
		getline(std::cin,Guess);


		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status){
			case EGuessStatus::Wrong_Length:
				std::cout<< "Please enter " <<BCGame.GetHiddenWordLength() << " word length!\n";
				break;
			case EGuessStatus::Not_Isogram:
				std::cout<< "Given word is not an isogram!/n";
				break;
			case EGuessStatus::Not_Lowercase:
				std::cout<< "Given word is not in lowercase!/n";
				break;
			default:
				//assume the guess is valid
				break;
		}
		std::cout<<std::endl;
	}while(Status != EGuessStatus::OK);

	return Guess;
}

bool AskToPlayAgain(){
	std::cout<<"Do you want to play again?"<<std::endl;
	FText Response = "";
	getline(std::cin,Response);

	return (Response[0]=='y' || Response[0]=='Y');
}

void PrintGameSummary(){
	if(BCGame.IsGameWon()){
		std::cout<<"Well done! You win!"<<std::endl;
	}else{
		std::cout<<"Bad luck this time! Try again!"<<std::endl;
	}
}
