// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayEffectTypes.h"
#include "Blueprint/UserWidget.h"
#include "ValueGauge.generated.h"

class UAbilitySystemComponent;
class UTextBlock;
class UProgressBar;

/**
 * 
 */
UCLASS()
class CRASH_API UValueGauge : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	virtual void NativePreConstruct() override;
	
	void SetAndBoundToGameplayAttribute(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayAttribute& Attribute, const FGameplayAttribute& MaxAttribute);
	
	void SetValue(float NewValue, float NewMaxValue);
	
private:
	
	void ValueChanged(const FOnAttributeChangeData& OnAttributeChangeData);
	
	void MaxValueChanged(const FOnAttributeChangeData& OnAttributeChangeData);
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> ProgressBar;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ValueText;
	
	UPROPERTY(EditAnywhere, Category = "Visual")
	FLinearColor BarColor;
	
	float CachedValue = 0;
	
	float CachedMaxValue = 0;
};
