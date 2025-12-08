// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	if (MovingActor != nullptr)
	{
		MovingComponent = MovingActor->FindComponentByClass<UMovingComponent>();
		if (MovingComponent != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("MovingComponent found on MovingActor"));
			MovingComponent->bIsMoving = true;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("MovingComponent NOT found on MovingActor"));
		}
	}
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
