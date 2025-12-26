// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Combo.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "CTags.h"

UGA_Combo::UGA_Combo()
{
	FGameplayTagContainer Container;
	Container.AddTag(Ability::BasicAttack);
	
	SetAssetTags(Container);
	
	BlockAbilitiesWithTag.AddTag(Ability::BasicAttack);
}

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
		
		UAbilityTask_WaitGameplayEvent* WaitComboChangeEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, Ability::Combo::Change, nullptr, false, false);
		WaitComboChangeEventTask->EventReceived.AddUniqueDynamic(this, &ThisClass::ComboChangedEventReceived);
		WaitComboChangeEventTask->ReadyForActivation();
		
		UAbilityTask_WaitGameplayEvent* WaitComboEndEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, Ability::Combo::End, nullptr, false, false);
		WaitComboEndEventTask->EventReceived.AddUniqueDynamic(this, &ThisClass::ComboEndedEventReceived);
		WaitComboEndEventTask->ReadyForActivation();
	}
}

void UGA_Combo::ComboChangedEventReceived(FGameplayEventData Payload)
{
	const FGameplayTag EventTag = Payload.EventTag;
	
	// Split Tag into parts and return the last part since that contains the info we need.
	
	TArray<FName> TagNames;
	
	UGameplayTagsManager::Get().SplitGameplayTagFName(EventTag, TagNames);
	
	NextComboName = TagNames.Last();
	
	UE_LOG(LogTemp, Warning, TEXT("next combo is %s"), *NextComboName.ToString());
}

void UGA_Combo::ComboEndedEventReceived(FGameplayEventData Payload)
{
	NextComboName = NAME_None;
		
	UE_LOG(LogTemp, Warning, TEXT("Combo opportunity missed."));
}
