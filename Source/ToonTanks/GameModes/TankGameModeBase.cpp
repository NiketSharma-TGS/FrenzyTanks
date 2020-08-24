// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"


void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// Get ref and game conditions

	// Call HandleGameStart()

}


void ActorDier(AActor* DeadActor) 
{
	// Check thy type of Actor that died
}

void HandleGameStart()
{
	// Start the countdown and such

	// Call the BP version
}

void HandleGameOver(bool PlayerWon)
{
	// Check for win condition

	// Call the BP version
}