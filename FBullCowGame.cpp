#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

FBullCowGame::FBullCowGame(){ Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const{ return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const{ return bGameIsWon; }

void FBullCowGame::Reset(){
	constexpr int32 MAX_TRIES = 5;
	const FString HIDDEN_WORD = "planet";

	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	MyMaxTries = MAX_TRIES;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FText Guess) const {
	//if the guess is not an isogram return error
	if(false){
		return EGuessStatus::Not_Isogram;
	}else if(false){//if the guess is not lowercase return error
		return EGuessStatus::Not_Lowercase;
	}else if(Guess.length()!=GetHiddenWordLength()){//if the guess length is wrong return error
		return EGuessStatus::Wrong_Length;
	}else{
		return EGuessStatus::OK;
	}
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess){
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();

	//loop through all letters in the hidden word
	for(int32 MHWChar = 0; MHWChar < WordLength ; MHWChar++){
		//compare letters against the guess
		for(int32 GChar = 0; GChar < WordLength ; GChar++){
			//if they match then
			if(Guess[GChar] == MyHiddenWord[MHWChar]){
				//if the same place
				if(MHWChar == GChar){
					BullCowCount.Bulls++;//increment bulls
				}else{
					BullCowCount.Cows++;//else increment cows
				}

			}
		}
	}
	if(BullCowCount.Bulls == WordLength){
		bGameIsWon=true;
	}else{
		bGameIsWon=false;
	}
	return BullCowCount;
}
