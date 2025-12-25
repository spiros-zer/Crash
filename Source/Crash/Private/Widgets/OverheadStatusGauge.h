// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OverheadStatusGauge.generated.h"

class UValueGauge;
class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class CRASH_API UOverheadStatusGauge : public UUserWidget
{
	GENERATED_BODY()

public:

	void ConfigureWithAsc(UAbilitySystemComponent* AbilitySystemComponent);
	
private:
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UValueGauge> HealthBar;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UValueGauge> ManaBar;
};
