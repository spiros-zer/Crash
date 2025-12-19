// Fill out your copyright notice in the Description page of Project Settings.


#include "CAbilitySystemComponent.h"

void UCAbilitySystemComponent::ApplyInitialEffects()
{
	for (const TSubclassOf<UGameplayEffect>& EffectClass : InitialEffects)
	{
		FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingSpec(EffectClass, 1.f, MakeEffectContext());
		
		ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	}
}
