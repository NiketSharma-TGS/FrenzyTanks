// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "Kismet/GameplayStatics.h"

void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	HandleGameStart();

}


void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	// Check the type of Actor that died for this comparing with PlayerTankReference
	// Basically checking if the dead actor is the player or a turret
	if (DeadActor == PlayerTank)
	{
		PlayerTank->DestructionHandler();
		HandleGameOver(false);
	}
	else if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
	{
		
		DestroyedTurret->DestructionHandler();
		
		if (--TargetTurrets == 0)
		{
			HandleGameOver(true);
		}
	}


	UE_LOG(LogTemp, Warning, TEXT("Actor Died"));
}

void ATankGameModeBase::HandleGameStart()
{
	
	TargetTurrets = GetTargetTurretCount();
	// 0 is the playerController index, will need to update this 
	//for split screen later
	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GameStart();
	
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
	GameOver(PlayerWon);
}

int32 ATankGameModeBase::GetTargetTurretCount()
{
	// TArray is to for OutActors given by the GetAllActorsClass
	TArray<AActor*> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);
	
	// Getting the number of turret, all turrets gone boom means ez win
	return TurretActors.Num();
}