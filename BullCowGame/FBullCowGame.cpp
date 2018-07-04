#include "FBullCowGame.h"
#include<map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame() {	Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }


void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "planet";
	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}



EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) //if guess is not an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) //if gues is not  all in lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength())  //not of appropriate length
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}


//receives a valid guess,increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	++MyCurrentTry;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); //assuming the same length as Guess

	for (int32 i = 0; i < WordLength; i++)
	{
		for (int32 j = 0; j < WordLength; j++)
		{
 			if (Guess[j] == MyHiddenWord[i])
			{
				if (j == i)
				{
					++BullCowCount.Bulls;
				}
				else
				{
					++BullCowCount.Cows;
				}
			}

		}

	}
	if (BullCowCount.Bulls == WordLength)
	{
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
	if (Word.length() <= 1) { return true; } //ofc 0 and 1 letter words will ALWAYS be isograms

	TMap<char, bool> LetterSeen; //a MAP

	for (auto Letter : Word) //Range based for loop| this is for all letters of the Word| auto finds a data type for us ;)
	{
		Letter = tolower(Letter);  //to handle mixed case
		
		if (LetterSeen[Letter])
			return false;
		else
			LetterSeen[Letter] = true;
	}

	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))  //if not a lowercase letter
			return false;
	}
	
	return true;
}

