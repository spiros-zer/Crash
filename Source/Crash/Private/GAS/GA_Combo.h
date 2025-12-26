// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CGameplayAbility.h"
#include "GA_Combo.generated.h"

/**
 * 
 */
UCLASS()
class CRASH_API UGA_Combo : public UCGameplayAbility
{
	GENERATED_BODY()
	
public:
	
	UGA_Combo();

		virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
protected:
	
	UFUNCTION()
	void ComboChangedEventReceived(FGameplayEventData Payload);
	
	UFUNCTION()
	void ComboEndedEventReceived(FGameplayEventData Payload);
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> ComboMontage;
	
	FName NextComboName;
};
