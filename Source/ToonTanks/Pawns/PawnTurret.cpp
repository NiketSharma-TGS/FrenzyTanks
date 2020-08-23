// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
    Super::BeginPlay();

    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

    /* Using PlayerPawn as an refence for the player controlled tank actor
     Zero is for the player Pawn index set in the instance of PawnTank placed in the world.
     Look more into GetPlayerPawn() later */

    PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0)); 
}


void APawnTurret::DestructionHandler()
{
    // Call the OG to play effects first then move to the overridden logic 
    Super::DestructionHandler();
    Destroy();
}


// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!PlayerPawn || ReturnDistanceToPlayer() > FireRange)
    {
        return;
    }

    TurretRotator(PlayerPawn->GetActorLocation());

}

void APawnTurret::CheckFireCondition()
{
    // If Player == null || is Dead THEN BAIL!!

    // a check to see if the player exists in the world yet
    if (!PlayerPawn) 
    {
        return;
    }
    
    // IF Player IS in range THEN FIRE!! 
    if (ReturnDistanceToPlayer() <= FireRange)
    {
        Fire();
        
    }

    
}


float APawnTurret::ReturnDistanceToPlayer()
{
    if (!PlayerPawn)
    {   
        // because some value is to be returned if it fails (double check)
        return 0.0f;
    }

    // Distance between playerPawn and the current posseded Actor
    float Distance = FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
    return Distance;

}