// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DamageEffectWidget.generated.h"

/**
 * 
 */
UCLASS()
class CODINGPLAYGROUND_API UDamageEffectWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "DamageEffect")
	void PlayDamageEffect();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "RespawnEffect")
	void PlayRespawnEffect();

};
