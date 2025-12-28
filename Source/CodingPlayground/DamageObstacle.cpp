// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageObstacle.h"
#include "Components/BoxComponent.h"
#include "CodingPlaygroundCharacter.h"

// Sets default values
ADamageObstacle::ADamageObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DamageBox = CreateDefaultSubobject<UBoxComponent>(TEXT("DamageBox"));
	RootComponent = DamageBox;
}

// Called when the game starts or when spawned
void ADamageObstacle::BeginPlay()
{
	Super::BeginPlay();
	DamageBox->OnComponentBeginOverlap.AddDynamic(this, &ADamageObstacle::OverlapStart);
	
}

// Called every frame
void ADamageObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADamageObstacle::OverlapStart(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	ACodingPlaygroundCharacter* Player = Cast<ACodingPlaygroundCharacter>(OtherActor);
	if (Player)
	{
		Player->DealtDamage(DamageAmount);
	}
	UE_LOG(LogTemp, Warning, TEXT("Damage obstacle triggered, player damaged"));
}

