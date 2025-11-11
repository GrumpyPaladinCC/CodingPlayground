// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckpointSystem.generated.h"

UCLASS()
class CODINGPLAYGROUND_API ACheckpointSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckpointSystem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OverlapStart(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor, 
	class UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, Category = "Checkpoint")
	FVector CheckpointLocation;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Checkpoint")
	class UBoxComponent* CheckpointBox;

	class StaticMeshComponent* CheckpointMesh;

};

