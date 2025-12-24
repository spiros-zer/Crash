// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayWidget.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "ValueGauge.h"
#include "GAS/CAttributeSet.h"

void UGameplayWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(GetOwningPlayerPawn());
	if (!AbilitySystemInterface) return;
	
	AbilitySystemComponent = AbilitySystemInterface->GetAbilitySystemComponent();
	check(IsValid(AbilitySystemComponent));
	
	HealthBar->SetAndBoundToGameplayAttribute(AbilitySystemComponent, UCAttributeSet::GetHealthAttribute(), UCAttributeSet::GetMaxHealthAttribute());
	
	ManaBar->SetAndBoundToGameplayAttribute(AbilitySystemComponent, UCAttributeSet::GetManaAttribute(), UCAttributeSet::GetMaxManaAttribute());
}
