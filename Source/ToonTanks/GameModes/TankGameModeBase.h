// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

class APawnTurret;
class APawnTank;
UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()


private:

	APawnTank* PlayerTank;
	int32 TargetTurrets = 0;

	int32 GetTargetTurretCount();
	// The logic is handled here, the functionality to display this is handled in BPs
	void HandleGameStart();
	void HandleGameOver(bool PlayerWon);

	

public:

	void ActorDied(AActor* DeadActor);

protected:

	virtual void BeginPlay() override;

	// To allow them to the BP derived classes which will take care of the timers and such
	UFUNCTION(BlueprintImplementableEvent)  
	void GameStart();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon);
	
};
