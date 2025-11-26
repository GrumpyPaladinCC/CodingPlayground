// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingComponent.h"

// Sets default values for this component's properties
UMovingComponent::UMovingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMovingComponent::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetOwner()->GetActorLocation();
	TargetLocation = StartLocation + DesiredLocation;
}


// Called every frame
void UMovingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsMoving)
	{
		CurrentLocation = GetOwner()->GetActorLocation();

		float MovementSpeed = DesiredLocation.Size() / MovementTime;

		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, MovementSpeed);
		
		GetOwner()->SetActorLocation(NewLocation);
		UE_LOG(LogTemp, Warning, TEXT("Ticking and Moving: %s"), bIsMoving ? TEXT("TRUE") : TEXT("FALSE"));
	}

}

