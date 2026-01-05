// Copyright Epic Games, Inc. All Rights Reserved.

#include "CodingPlaygroundCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "CodingPlayground.h"


ACodingPlaygroundCharacter::ACodingPlaygroundCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void ACodingPlaygroundCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACodingPlaygroundCharacter::Move);
		
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ACodingPlaygroundCharacter::Look);
		
		// Sprinting
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &ACodingPlaygroundCharacter::DoSprintStart);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ACodingPlaygroundCharacter::StopSprint);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACodingPlaygroundCharacter::Look);

		// Respawn
		EnhancedInputComponent->BindAction(RespawnAction, ETriggerEvent::Started, this, &ACodingPlaygroundCharacter::DoRespawn);
	}
	else
	{
		UE_LOG(LogCodingPlayground, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ACodingPlaygroundCharacter::BeginPlay()
{
	Super::BeginPlay();
	// Set the respawn location to the starting location
	RespawnLocation = GetActorLocation();
	CurrentHealth = MaxHealth;
	DefaultMaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;


	UE_LOG(LogCodingPlayground, Error, TEXT("'%s' Initial Respawn Location set to %s"), *GetNameSafe(this), *RespawnLocation.ToString());
	UE_LOG(LogCodingPlayground, Error, TEXT("Initial Health set to %f"), CurrentHealth);
}

void ACodingPlaygroundCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void ACodingPlaygroundCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void ACodingPlaygroundCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void ACodingPlaygroundCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void ACodingPlaygroundCharacter::DoJumpStart()
{
	// signal the character to jump
	Jump();
}

void ACodingPlaygroundCharacter::DoJumpEnd()
{
	// signal the character to stop jumping
	StopJumping();
}

void ACodingPlaygroundCharacter::SetRespawnLocation(const FVector NewLocation)
{
	RespawnLocation = NewLocation;
}

void ACodingPlaygroundCharacter::DealtDamage(float DamageAmount)
{
	CurrentHealth -= DamageAmount;
	UE_LOG(LogCodingPlayground, Error, TEXT("Damage has been taken! equal to '%f'"),DamageAmount);
	
	if (CurrentHealth <= 0.f)
	{
		if (OnPlayerRespawn.IsBound())
		{
			OnPlayerRespawn.Broadcast();
		}
		
		UE_LOG(LogCodingPlayground, Error, TEXT("'%s' Health has reached zero, respawning..."), *GetNameSafe(this));
		DoRespawn();
		CurrentHealth = MaxHealth;
		UE_LOG(LogCodingPlayground, Error, TEXT("'%s' Health reset to %f after respawn"), *GetNameSafe(this), CurrentHealth);
	}
	else
	{
		if (OnPlayerDamage.IsBound())
		{
			OnPlayerDamage.Broadcast();
		}
	}

	
}

void ACodingPlaygroundCharacter::DoSprintStart()
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultMaxWalkSpeed * SpeedMultiplier;
	
}

void ACodingPlaygroundCharacter::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultMaxWalkSpeed;
	UE_LOG(LogCodingPlayground, Error, TEXT("Stopped Sprinting with the new MaxWalkSpeed of %f"), GetCharacterMovement()->MaxWalkSpeed);
	
}

void ACodingPlaygroundCharacter::DoRespawn()
{
	SetActorLocation(RespawnLocation);
	UE_LOG(LogCodingPlayground, Error, TEXT("'%s' Respawned at location %s"), *GetNameSafe(this), *RespawnLocation.ToString());
}
