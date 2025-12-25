// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"

#include "CAbilitySystemComponent.generated.h"


UCLASS()
class CRASH_API UCAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:

	void ApplyInitialEffects();
	
	/** 
	 * Gives the ASC the abilities of a character.
	 */
	void GiveInitialAbilities();
	
private:
	
	UPROPERTY(EditDefaultsOnly, Category = "GameplayEffect")
	TArray<TSubclassOf<UGameplayEffect>> InitialEffects;

	/** 
	 * Unique character abilities, that the character has to learn in order to perform.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbilites")
	TArray<TSubclassOf<UGameplayAbility>> Abilities;
	
	/** 
	 * Abilities already learnt by default.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbilites")
	TArray<TSubclassOf<UGameplayAbility>> BasicAbilities;
};
