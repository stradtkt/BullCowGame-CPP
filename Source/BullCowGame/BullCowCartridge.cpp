// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    SetupGame();
    PrintLine(TEXT("The number of valid words is: %i"), GetValidWords(Words).Num());
    PrintLine(TEXT("The number of possible words is %i"), Words.Num());
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if(bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else 
    {
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = TEXT("cake");
    Lives = HiddenWord.Len();
    bGameOver = false;
    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives"), Lives);
    PrintLine(TEXT("Type in your guess, and\npress enter to continue..."));
    const TCHAR HW[] = TEXT("cakes");
    PrintLine(TEXT("Character 1 of the hidden word is: %c"), HiddenWord[0]);
    IsIsogram(HiddenWord);
}
void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress enter to play again."));
}
void UBullCowCartridge::ProcessGuess(FString Guess)
{
    if(Guess == HiddenWord)
    {
        PrintLine(TEXT("You have won!!"));
        EndGame();
        return;
    }
    if(Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("You have %i lives remaining before losing!"), Lives);
        PrintLine(TEXT("The hidden word is %i characters long."), HiddenWord.Len());
        return;
    }
    if(!IsIsogram(Guess))
    {
        PrintLine(TEXT("There should be no repeating letters please try again..."));
        return;
    }
    PrintLine(TEXT("Lost a life!"));
    --Lives;
    if(Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You have no lives left!"));
        PrintLine(TEXT("The hidden word was %s."), *HiddenWord);
        EndGame();
        return;
    }
    PrintLine(TEXT("Guess again, you have %i lives left"), Lives);
}
bool UBullCowCartridge::IsIsogram(FString Word) const
{
    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if(Word[Index] == Word[Comparison])
            {
                return false;
            }
        }
    }
    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(TArray<FString> WordList) const
{
    TArray<FString> ValidWords;

    for (int32 Index = 0; Index < 10; Index++)
    {
        if(Words[Index].Len() >= 4 && Words[Index].Len() <= 8)
        {
            if(IsIsogram(Words[Index])) 
            {
                ValidWords.Emplace(Words[Index]);
            }
        }
    }
    return ValidWords;
}