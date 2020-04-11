// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Dictonary.h"
#include "Cow.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Engine/TargetPoint.h"
#include "Math/UnrealMathUtility.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    Isogram = GetValidWords(Dictonary);
    SetupGame();
}
void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
    if (bGameOver == true)  // if the game is over then do ClearScreen() and re SetupGame() the game
    {    
       ClearScreen();
       SetupGame();
    }
    else  // else Checking The PlayerGuess      
    {
        ProcessGuess(PlayerInput);   
    }
}

void UBullCowCartridge::SetupGame()
{
    // Welcoming The Player
    PrintLine(TEXT("Welcome to Bull Cow!"));

    HiddenWord = Isogram[FMath::RandRange(0,GetValidWords(Dictonary).Num()-1)];
    Lives = HiddenWord.Len();
    
    PrintLine(TEXT("where are %i letter word"), HiddenWord.Len());
    PrintLine(TEXT("You Have %i Lives \npress enter to continue"),Lives);
    PrintLine(TEXT("The HiddenWord is %s "),*HiddenWord);
}

void UBullCowCartridge::EndGame()
{   
    bGameOver = true;
    PrintLine(TEXT("Press Enter to Play again."));
    return;
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    if (HiddenWord == Guess)
    {
        PrintLine(TEXT("You Have Won!"));
        EndGame();
        return;     
    }

    if (Guess.Len() != HiddenWord.Len()) 
    {
        PrintLine(TEXT("The Hidden Word is %i Characters Long."), HiddenWord.Len());
        return;
    }
        // check the Isogram
    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("No Repeating Letters, Guess Again!"));
        return;
    }
       
    --Lives;     // Remove Life        
    PrintLine(TEXT("You Have Lost a Live! \nYou Have %i Lives left!"),Lives);

    if (Lives <= 0)
    {   
        ClearScreen();
        PrintLine(TEXT("no lives left!"));
        PrintLine(TEXT("The HiddenWord was: %s"), *HiddenWord);
        EndGame();
        return;
    }
	
    FBullCowCount Score = GetBullCows(Guess);
    SpawnBulls(Score);
    SpawnCows(Score);

    PrintLine(TEXT("You Have %i bulls and %i Cows"),Score.Bulls, Score.Cows);
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    int32 Index = 0 ;
    int32 Comparison = Index + 1;
    for (Index; Index < Word.Len(); Index++)
    {
        for (Comparison; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Index] == Word[Comparison])
            {
                return false;
            }
        }
    }
    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWords;
    for (FString Word : WordList)
    {
        if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
        {
           ValidWords.Emplace(Word);
        }
    }
    return ValidWords;
}    

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
    FBullCowCount Count;

    for (int32 Index = 0; Index < Guess.Len(); Index++)
    {
        if (Guess[Index] == HiddenWord[Index])
        {
            Count.Bulls++;
            continue;
        } 

        for (int32 HiddenIndex = 1; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            if (Guess[Index] == HiddenWord[HiddenIndex])
            {
                Count.Cows++;
                break;
            } 
        } 
    }
    return Count;
}

void UBullCowCartridge::DestroyCow()
{
    for (AActor* Cow : Cows)  
    {
        Cow->Destroy();  
    }
}

void UBullCowCartridge::DestroyBull()
{
    for (AActor* Bull : Bulls)
    {
        Bull->Destroy();
    }
}

void UBullCowCartridge::SpawnBulls(FBullCowCount Count)
{
    DestroyBull();

	for (int32 i = 0; i < Count.Bulls; i++)
    {
        FTransform Transform = BullSpawnPoints->GetTransform();
        FVector Location = Transform.GetLocation();
        Location += FVector(0, 50 * i, 0);
        Transform.SetLocation(Location);
        ACow* Bull = GetWorld()->SpawnActor<ACow>(BP_BullClass, Transform);
        Bulls.Add(Bull);
    }
}

void UBullCowCartridge::SpawnCows(FBullCowCount Count)
{
    DestroyCow();

    for (int32 j = 0; j < Count.Bulls; j++)
    {
        FTransform Transform = CowSpawnPoints->GetTransform();
        FVector Location = Transform.GetLocation();
        Location += FVector(0, 50 * j, 0);
        Transform.SetLocation(Location);
        ACow* Cow = GetWorld()->SpawnActor<ACow>(BP_CowClass, Transform);
        Cows.Add(Cow);
    }
}