// Fill out your copyright notice in the Description page of Project Settings.


#include "ValueGauge.h"

#include "AbilitySystemComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "ProfilingDebugging/CookStats.h"

void UValueGauge::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	ProgressBar->SetFillColorAndOpacity(BarColor);
}

void UValueGauge::SetAndBoundToGameplayAttribute(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayAttribute& Attribute, const FGameplayAttribute& MaxAttribute)
{
	if (!IsValid(AbilitySystemComponent)) return;
	
	bool bFound = false;
	
	const float Value = AbilitySystemComponent->GetGameplayAttributeValue(Attribute, bFound);
	
	const float MaxValue = AbilitySystemComponent->GetGameplayAttributeValue(MaxAttribute, bFound);
	
	if (!bFound)
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		SetValue(Value, MaxValue);
	}
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(this, &ThisClass::ValueChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MaxAttribute).AddUObject(this, &ThisClass::MaxValueChanged);
}

void UValueGauge::SetValue(float NewValue, float NewMaxValue)
{
	// Setting progressbar
	
	if (!NewMaxValue)
	{
		SetVisibility(ESlateVisibility::Hidden);
	
		return;
	}
	
	CachedValue = NewValue;
	
	CachedMaxValue = CachedMaxValue;
	
	const float Percent = NewValue / NewMaxValue;
	
	ProgressBar->SetPercent(Percent);
	
	// Setting text
	
	FNumberFormattingOptions FormattingOptions;
	FormattingOptions.SetMaximumFractionalDigits(0);
	
	const FText UnformattedText = FText::FromString("{0}/{1}");
	FFormatNamedArguments Args;
	Args.Add("0", FText::AsNumber(NewValue, &FormattingOptions));
	Args.Add("1", FText::AsNumber(NewMaxValue, &FormattingOptions));
	
	ValueText->SetText(FText::Format(UnformattedText, Args));
}

void UValueGauge::ValueChanged(const FOnAttributeChangeData& OnAttributeChangeData)
{
	SetValue(OnAttributeChangeData.NewValue, CachedMaxValue);
}

void UValueGauge::MaxValueChanged(const FOnAttributeChangeData& OnAttributeChangeData)
{
	SetValue(CachedValue, OnAttributeChangeData.NewValue);
}
