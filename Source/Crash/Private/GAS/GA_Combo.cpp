// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Combo.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"

void UGA_Combo::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	if (!K2_CommitAbility())
	{
		K2_EndAbility();
		
		return;
	}
	
	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		UAbilityTask_PlayMontageAndWait* PlayComboMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, ComboMontage);
		PlayComboMontageTask->OnBlendOut.AddUniqueDynamic(this, &ThisClass::K2_EndAbility);	
		PlayComboMontageTask->OnCancelled.AddUniqueDynamic(this, &ThisClass::K2_EndAbility);	
		PlayComboMontageTask->OnCompleted.AddUniqueDynamic(this, &ThisClass::K2_EndAbility);	
		PlayComboMontageTask->OnInterrupted.AddUniqueDynamic(this, &ThisClass::K2_EndAbility);	
		PlayComboMontageTask->ReadyForActivation();
	}
}
