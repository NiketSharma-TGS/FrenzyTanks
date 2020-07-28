// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


APawnTank::APawnTank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);  // RootComponent defined in the parent class

	Camera = CreateAbstractDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Rotate();
	Move();

}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// This always get updated, a value of 0 is passed if no input is passed
	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput); // This always get updated, a value of 0 is passed if no input is passed

	// For D & A
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotateInput);

}


void APawnTank::CalculateMoveInput(float Value)
{
	// Using DeltaTimeSeconds to make this Framerate independant
	MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
}

void APawnTank::CalculateRotateInput(float Value)
{
	float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds; // Try withou declaring a new FRotator
	FRotator Rotation = FRotator(0, RotateAmount, 0); //Change rotateAmt to Rotation
	RotationDirection = FQuat(Rotation);

}

void APawnTank::Move()
{
	AddActorLocalOffset(MoveDirection, true); //A sweep check is for collisions 
}

void APawnTank::Rotate()
{
	AddActorLocalRotation(RotationDirection, true);
}