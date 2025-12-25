// Fill out your copyright notice in the Description page of Project Settings.


#include "OverheadStatusGauge.h"

#include "AbilitySystemComponent.h"
#include "ValueGauge.h"
#include "GAS/CAttributeSet.h"

void UOverheadStatusGauge::ConfigureWithAsc(UAbilitySystemComponent* AbilitySystemComponent)
{
	check(IsValid(AbilitySystemComponent));
	
	HealthBar->SetAndBoundToGameplayAttribute(AbilitySystemComponent, UCAttributeSet::GetHealthAttribute(), UCAttributeSet::GetMaxHealthAttribute());
	
	ManaBar->SetAndBoundToGameplayAttribute(AbilitySystemComponent, UCAttributeSet::GetManaAttribute(), UCAttributeSet::GetMaxManaAttribute());
}
