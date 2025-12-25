// Fill out your copyright notice in the Description page of Project Settings.


#include "CAbilitySystemComponent.h"

void UCAbilitySystemComponent::ApplyInitialEffects()
{
	if (!GetOwner()->HasAuthority()) return;
	
	for (const TSubclassOf<UGameplayEffect>& EffectClass : InitialEffects)
	{
		FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingSpec(EffectClass, 1.f, MakeEffectContext());
		
		ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	}
}

void UCAbilitySystemComponent::GiveInitialAbilities()
{
	if (!GetOwner()->HasAuthority()) return;
	
	// Giving the abilities with level 0 to indicate they are not yet learned.
	
	for (const TSubclassOf<UGameplayAbility>& AbilityClass : Abilities)
	{
		GiveAbility(FGameplayAbilitySpec(AbilityClass, 0, -1, nullptr));
	}
	
	// Giving the base abilities.
	
	for (const TSubclassOf<UGameplayAbility>& AbilityClass : BasicAbilities)
	{
		GiveAbility(FGameplayAbilitySpec(AbilityClass, 1, -1, nullptr));
	}
}
