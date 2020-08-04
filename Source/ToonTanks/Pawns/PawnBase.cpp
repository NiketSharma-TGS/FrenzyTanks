// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "ToonTanks/Actors/ProjectileBase.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));    
	//Root Component, this will get defined as the root component by the engine anyway but just doing this for safety
	RootComponent = CapsuleComp;  // This is AActor = Pawn so yeah, correct

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	//SetupAttachment() is a USceneComponent function, it takes a USceneComp argument, so passing RootComponent here because it qualifies and contains the CapsuleComp data 
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	// To spawn the projectile from turret
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));  
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void APawnBase::TurretRotator(FVector LookAtTarget) // Argument recieves from the child class
{

	// So we only rotate around the turret and not up or down

	FVector LookAtTargetClean = FVector(LookAtTarget.X, LookAtTarget.Y, TurretMesh->GetComponentLocation().Z);
	FVector Startlocation = TurretMesh->GetComponentLocation();

	FRotator TurretRotation = FVector(LookAtTargetClean - Startlocation).Rotation();
	TurretMesh->SetWorldRotation(TurretRotation);

}

void APawnBase::Fire()
{
	// spawnPoints and location update
	if (ProjectileClass)
	{
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
		
		AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation);
		
		// Passing a ref of this class as the new parent actor
		TempProjectile->SetOwner(this);
	}
}

void APawnBase::DestructionHandler()
{
	// Play effects

	// Do child overrrrrrrrides

	// Hide dead stuff
}


