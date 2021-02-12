// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"
//#include "Math/UnrealMathUtility.h"
void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    GetValidWords(Word);
    SetupGame();
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
    HiddenWord=ValidWords[FMath::RandRange(0,ValidWords.Num()-1)];
    PrintLine(TEXT("Welcome to the Bull Cow Game\nThe Hidden Word is %d character\n"),HiddenWord.Len());
    PrintLine(TEXT("The word is %s\n"),*HiddenWord);//Debug Line
    lives=(HiddenWord.Len())*2;
    PrintLine(TEXT("You have %i lives\n"),lives);
    bGameOver=false;
}
void UBullCowCartridge::EndGame()
{
    bGameOver=true;
    PrintLine(TEXT("You are out of lives\nPress enter to play again."));
}
void UBullCowCartridge::ProcessGuess(FString Guess)
{
    ClearScreen();
    if(Guess==HiddenWord&&lives>0)
    {
        PrintLine(TEXT("You have Won!"));
        EndGame();
    }
    else
    {
        if(lives<=0)
            EndGame();
        else
        {
            int t=HiddenWord.Len();
            if(Guess.Len()!=HiddenWord.Len())
                PrintLine(TEXT("The Hidden Word is of %d characters.\nPlease try again\n"),t);
            else
            {
                PrintLine(TEXT("You are Wrong!\nYou lose 1 live\nLives remaining %i\n"),lives);
                int32 Bulls,Cows;
                GetBullCows(Guess,Bulls,Cows);
                PrintLine(TEXT("You have %i Bulls and %i Cows"),Bulls,Cows);
                lives--;
            }
        }
    }
}
bool UBullCowCartridge::IsIsogram(FString Word)
{
    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Index] == Word[Comparison])
            {
                return false;
            }
        }   
    }
    return true;
}
void UBullCowCartridge::GetValidWords(TArray<FString> lw)
{
    for(int32 i=0;i<lw.Num();i++)
    {
        if(lw[i].Len()<=8&&lw[i].Len()>=4&&(IsIsogram(lw[i])==true))
        {
            ValidWords.Add(lw[i]);
        }
    }
}
void UBullCowCartridge::GetBullCows(const FString& Guess,int32& B,int32& C)
{
    B=0;
    C=0;
    for(int32 gi=0;gi<Guess.Len();gi++)
    {
        if(Guess[gi]==HiddenWord[gi])
        {
            B++;
            continue;
        }
        for(int hi=0;hi<HiddenWord.Len();hi++)
        {
            if(Guess[gi]==HiddenWord[hi])
            {
                C++;
                break;
            }
        }
    }
}