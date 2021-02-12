// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void SetupGame();
	void EndGame();
	bool IsIsogram(FString Word);
	void GetValidWords(TArray<FString> lw);
	void ProcessGuess(FString Guess);
	void GetBullCows(const FString& Guess,int32& B,int32& C);
	// Your declarations go below!
	private:
	FString HiddenWord;
	int32 lives;
	bool bGameOver;
	TArray<FString> ValidWords;
};
