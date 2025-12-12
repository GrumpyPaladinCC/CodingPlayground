// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	if (MovingActor)
	{
		MovingComponent = MovingActor->FindComponentByClass<UMovingComponent>();
		if (MovingComponent != nullptr)
		{
			UE_LOG(LogTemp, Display, TEXT("Component Found"));
			
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("Component NOT found"));
		}
	}
	if (!IsPressurePlate)
	OnComponentBeginOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapBegin);
	OnComponentEndOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapEnd);
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTriggerComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (MovingComponent)
	{
		MovingComponent->bIsMoving = true;
		UE_LOG(LogTemp, Display, TEXT("Component moving"));
	}
}

void UTriggerComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (MovingComponent)
	{
		MovingComponent->bIsMoving = false;
		UE_LOG(LogTemp, Display, TEXT("Component NOT moving"));
	}
}
