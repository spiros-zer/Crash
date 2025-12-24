// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayWidget.generated.h"

class UAbilitySystemComponent;
class UValueGauge;
/**
 * 
 */
UCLASS()
class CRASH_API UGameplayWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	
	virtual void NativeOnInitialized() override;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UValueGauge> HealthBar;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UValueGauge> ManaBar;
	
private:
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
};
