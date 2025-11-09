// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	StartingLocation = GetActorLocation();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	FVector CurrentLocation = GetActorLocation();

	CurrentLocation += (PlatformSpeed * DeltaTime);
	SetActorLocation(CurrentLocation);

	DistanceMoved = GetDistanceMoved();

	if (DistanceMoved >= MaxDistance)
	{
		FVector MoveDirection = PlatformSpeed.GetSafeNormal();
		StartingLocation += MoveDirection * MaxDistance;
		SetActorLocation(StartingLocation);
		PlatformSpeed = -PlatformSpeed;
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	FRotator RoationToAdd = RotationVelocity * DeltaTime;
	AddActorLocalRotation(RoationToAdd);
}

float AMovingPlatform::GetDistanceMoved()
{
	return FVector::Dist(StartingLocation, GetActorLocation());
}

