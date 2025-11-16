// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckpointSystem.h"
#include "Components/BoxComponent.h"
#include "CodingPlaygroundCharacter.h"

// Sets default values
ACheckpointSystem::ACheckpointSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CheckpointBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CheckpointBox"));
	RootComponent = CheckpointBox;
	CheckpointLocation = GetActorLocation();

}

// Called when the game starts or when spawned
void ACheckpointSystem::BeginPlay()
{
	Super::BeginPlay();
	CheckpointBox->OnComponentBeginOverlap.AddDynamic(this, &ACheckpointSystem::OverlapStart);
	CheckpointLocation = GetActorLocation();
}

void ACheckpointSystem::OverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACodingPlaygroundCharacter* Player = Cast<ACodingPlaygroundCharacter>(OtherActor);
	if (Player)
	{
		Player->SetRespawnLocation(CheckpointLocation);
	}
	UE_LOG(LogTemp, Display, TEXT("Checkpoint reached, new respawn point set"));
}

// Called every frame
void ACheckpointSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

