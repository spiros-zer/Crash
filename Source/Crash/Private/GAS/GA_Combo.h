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
	
	/** 
	 * Maps the combo names as defined by their anim montage sections to gameplay effects.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effect")
	TMap<FName, TSubclassOf<UGameplayEffect>> DamageEffectMap;
	
	/** 
	 * Default gameplay effect to use if none is found.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effect")
	TSubclassOf<UGameplayEffect> DefaultDamageEffect;
	
private:
	
	UFUNCTION()
	void ComboChangedEventReceived(FGameplayEventData Payload);
	
	UFUNCTION()
	void ComboEndedEventReceived(FGameplayEventData Payload);
	
	void SetupWaitComboInputPress();
	
	UFUNCTION()
	void HandleInputPressed(float TimeWaited);
	
	void TryCommitCombo();
	
	UPROPERTY(EditDefaultsOnly, Category = "Targetting")
	float TargetSweepSphere = 30.f;
	
	/** 
	 * Called on Ability::Combo::Damage gameplay event received.
	 * @param Data Contains the locations for the sweep.
	 */
	UFUNCTION()
	void DoDamage(FGameplayEventData Data);
	
	TSubclassOf<UGameplayEffect> GetDamageEffectForCurrentCombo() const;
	
	FName NextComboName;
};
