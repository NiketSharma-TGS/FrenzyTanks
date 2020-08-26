// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"


void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// Get ref and game conditions

	// Call HandleGameStart()

}


void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	// Check thy type of Actor that died
	UE_LOG(LogTemp, Warning, TEXT("Pawn Died"));
}

void ATankGameModeBase::HandleGameStart()
{
	// Start the countdown and such

	// Call the BP version
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
	// Check for win condition

	// Call the BP version
}