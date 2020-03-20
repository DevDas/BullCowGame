// Fill out your copyright notice in the Description page of Project Settings.


#include "Cow.h"
#include "Components/StaticMeshComponent.h"
#include <Runtime\CoreUObject\Public\UObject\ConstructorHelpers.h>


// Sets default values
ACow::ACow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CowMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CowMeshComp"));
	RootComponent = CowMeshComp;

	//const static ConstructorHelpers::FObjectFinder<UStaticMesh> CowMeshFinder = TEXT("/Game/Environment/UnrealCow/Meshes/SM_Toy_Cow.SM_Toy_Cow");

	//CowMeshComp->SetStaticMesh(CowMeshFinder.Object);
}

// Called when the game starts or when spawned
void ACow::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

