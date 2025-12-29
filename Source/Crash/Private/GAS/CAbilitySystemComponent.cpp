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
		Server_ApplyGameplayEffect(EffectClass);
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

void UCAbilitySystemComponent::ApplyFullStatEffect()
{
	Server_ApplyGameplayEffect(FullStatEffect);
}

void UCAbilitySystemComponent::HealthUpdated(const FOnAttributeChangeData& OnAttributeChangeData)
{
	check(DeathEffect);
	
	AActor* Owner = GetOwner();
	if (!IsValid(Owner)) return;
	if (!Owner->HasAuthority()) return;
	
	if (OnAttributeChangeData.NewValue <= 0)
	{
		Server_ApplyGameplayEffect(DeathEffect);
	}
}

void UCAbilitySystemComponent::Server_ApplyGameplayEffect(TSubclassOf<UGameplayEffect> GameplayEffect, int Level)
{
	const AActor* Owner = GetOwner();
	if (!IsValid(Owner)) return;
	if (!Owner->HasAuthority()) return;
	
	FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingSpec(GameplayEffect, Level, MakeEffectContext());
		
	ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}
