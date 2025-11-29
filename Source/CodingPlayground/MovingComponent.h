// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MovingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CODINGPLAYGROUND_API UMovingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMovingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector CurrentLocation;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementTime = 4.0;

	
	UPROPERTY(EditAnywhere, Category="Movement")
	FVector DesiredLocation;

	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector TargetLocation;

	UPROPERTY(EditAnywhere, Category = "Movement")
	bool bIsMoving = false;

	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector StartLocation;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	bool ReachedLocation = false;
};
