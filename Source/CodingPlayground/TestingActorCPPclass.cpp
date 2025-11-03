// Fill out your copyright notice in the Description page of Project Settings.


#include "TestingActorCPPclass.h"

// Sets default values
ATestingActorCPPclass::ATestingActorCPPclass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestingActorCPPclass::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Error, TEXT("Hello from C++ Actor"));
}

// Called every frame
void ATestingActorCPPclass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

