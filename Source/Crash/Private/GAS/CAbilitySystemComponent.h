// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CGameplayAbilityTypes.h"

#include "CAbilitySystemComponent.generated.h"


UCLASS()
class CRASH_API UCAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:

	UCAbilitySystemComponent();

	void ApplyInitialEffects();
	
	/** 
	 * Gives the ASC the abilities of a character.
	 */
	void GiveInitialAbilities();
	
private:
	
	/** 
	 * Called when health attributes changes.
	 */
	void HealthUpdated(const FOnAttributeChangeData& OnAttributeChangeData);
	
	UPROPERTY(EditDefaultsOnly, Category = "GameplayEffect")
	TArray<TSubclassOf<UGameplayEffect>> InitialEffects;

	UPROPERTY(EditDefaultsOnly, Category = "GameplayEffect")
	TSubclassOf<UGameplayEffect> DeathEffect;
	
	/** 
	 * Unique character abilities, that the character has to learn in order to perform.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbilites")
	TMap<ECAbilityInputID, TSubclassOf<UGameplayAbility>> Abilities;
	
	/** 
	 * Abilities already learnt by default.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbilites")
	TMap<ECAbilityInputID, TSubclassOf<UGameplayAbility>> BasicAbilities;
};
