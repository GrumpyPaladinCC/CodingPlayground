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

	UFUNCTION(BlueprintCallable, Category = "DamageEffect")
	void PlayDamageEffect()
	{
		if (FadeAnimation)
		{
			
			PlayAnimation(FadeAnimation);
			UE_LOG(LogTemp, Warning, TEXT("Playing Damage Effect Animation"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("FadingAnimation is not set!"));
		}
	}

protected:
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* FadeAnimation;
};
