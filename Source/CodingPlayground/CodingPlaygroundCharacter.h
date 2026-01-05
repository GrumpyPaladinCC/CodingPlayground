// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Delegates/DelegateCombinations.h"
#include "CodingPlaygroundCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;
class UDamageEffectWidget;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerEvent);

/**
 *  A simple player-controllable third person character
 *  Implements a controllable orbiting camera
 */
UCLASS(abstract)
class ACodingPlaygroundCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
protected:

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* RespawnAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MouseLookAction;

	UPROPERTY(EditAnywhere, Category = "Respawn")
	FVector RespawnLocation;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* SprintAction;

public:

	/** Constructor */
	ACodingPlaygroundCharacter();	
protected:

	/** Initialize input action bindings */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);


public:

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles look inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoLook(float Yaw, float Pitch);

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoRespawn();

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();

	UFUNCTION(BlueprintCallable, Category = "Respawn")
	virtual void SetRespawnLocation(const FVector NewLocation);

	UFUNCTION(BlueprintCallable, Category = "Health")
	void DealtDamage(float DamageAmount);

	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoSprintStart();
	
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void StopSprint();

private:
	float DefaultMaxWalkSpeed;
	

protected:
	UPROPERTY(EditAnywhere, Category="Health")
	float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	float CurrentHealth;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnPlayerEvent OnPlayerDamage;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnPlayerEvent OnPlayerRespawn;

	UPROPERTY(EditAnywhere, Category = "Speed")
	float SpeedMultiplier = 1.25f;

	UPROPERTY(EditAnywhere, Category = "UI")
	FString yes;

public:

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

