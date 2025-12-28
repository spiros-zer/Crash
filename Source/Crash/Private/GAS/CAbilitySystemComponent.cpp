// Fill out your copyright notice in the Description page of Project Settings.


#include "CAbilitySystemComponent.h"

#include "CAttributeSet.h"

UCAbilitySystemComponent::UCAbilitySystemComponent()
{
	GetGameplayAttributeValueChangeDelegate(UCAttributeSet::GetHealthAttribute()).AddUObject(this, &ThisClass::HealthUpdated);
}

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
	
	for (const TPair<ECAbilityInputID, TSubclassOf<UGameplayAbility>>& AbilityPair : Abilities)
	{
		GiveAbility(FGameplayAbilitySpec(AbilityPair.Value, 0, static_cast<int32>(AbilityPair.Key), nullptr));
	}
	
	// Giving the base abilities.
	
	for (const TPair<ECAbilityInputID, TSubclassOf<UGameplayAbility>>& AbilityPair : BasicAbilities)
	{
		GiveAbility(FGameplayAbilitySpec(AbilityPair.Value, 1, static_cast<int32>(AbilityPair.Key), nullptr));
	}
}

void UCAbilitySystemComponent::HealthUpdated(const FOnAttributeChangeData& OnAttributeChangeData)
{
	check(DeathEffect);
	
	AActor* Owner = GetOwner();
	if (!IsValid(Owner)) return;
	if (!Owner->HasAuthority()) return;
	
	if (OnAttributeChangeData.NewValue <= 0)
	{
		const FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingSpec(DeathEffect, 1.f, MakeEffectContext());
		
		ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	}
}
