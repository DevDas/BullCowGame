// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& PlayerInput) override;
	void SetupGame();
	void EndGame();
	void ProcessGuess(const FString& Guess);
	bool IsIsogram(const FString& Word) const;
	TArray<FString> GetValidWords(const TArray<FString>& WordList) const;
	TArray<FString>Isogram;
	FBullCowCount GetBullCows(const FString& Guess) const;

	// Your declarations go below!
private:
	FString HiddenWord;
	int32 Lives;
	bool bGameOver;

	//UPROPERTY(EditAnywhere, Category = "CowArray")
	//TArray<AActor*> Cows; // Delete Cow By Array System Direct

	UPROPERTY(EditAnywhere, Category = "CowArray")
	class ATargetPoint* CowSpawnPoints;
	TArray<AActor*> Cows;

	UPROPERTY(EditAnywhere, Category = "CowArray")
	TSubclassOf<class ACow> BP_CowClass;

	UPROPERTY(EditAnywhere, Category = "BullArray")
	class ATargetPoint* BullSpawnPoints;
	TArray<AActor*> Bulls;

	UPROPERTY(EditAnywhere, Category = "BullArray")
	TSubclassOf<class ACow> BP_BullClass;


public:
	void DestroyCow();
	void DestroyBull();
	void SpawnBulls(FBullCowCount Count);
	void SpawnCows(FBullCowCount Count);
};
