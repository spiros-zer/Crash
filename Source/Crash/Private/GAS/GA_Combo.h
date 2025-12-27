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
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> ComboMontage;
	
private:
	
	UFUNCTION()
	void ComboChangedEventReceived(FGameplayEventData Payload);
	
	UFUNCTION()
	void ComboEndedEventReceived(FGameplayEventData Payload);
	
	void SetupWaitComboInputPress();
	
	UFUNCTION()
	void HandleInputPressed(float TimeWaited);
	
	void TryCommitCombo();
	
	/** 
	 * Called on Ability::Combo::Damage gameplay event received.
	 * @param Data Contains the locations for the sweep.
	 */
	UFUNCTION()
	void DoDamage(FGameplayEventData Data);
	
	FName NextComboName;
};
