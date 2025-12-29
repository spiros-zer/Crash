// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Combo.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Abilities/Tasks/AbilityTask_WaitInputPress.h"
#include "GameplayEffect.h"
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
	
	if (K2_HasAuthority())
	{
		UAbilityTask_WaitGameplayEvent* WaitTargetEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, Ability::Combo::Damage);
		WaitTargetEventTask->EventReceived.AddUniqueDynamic(this, &ThisClass::DoDamage);
		WaitTargetEventTask->ReadyForActivation();
	}
	
	SetupWaitComboInputPress();
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

void UGA_Combo::SetupWaitComboInputPress()
{
	UAbilityTask_WaitInputPress* WaitInputPress = UAbilityTask_WaitInputPress::WaitInputPress(this);
	WaitInputPress->OnPress.AddUniqueDynamic(this, &ThisClass::HandleInputPressed);
	WaitInputPress->ReadyForActivation();
}

void UGA_Combo::HandleInputPressed(float TimeWaited)
{
	// Listen for inputs as soon as this one is handled
	
	SetupWaitComboInputPress();
	
	TryCommitCombo();
}

void UGA_Combo::TryCommitCombo()
{
	if (NextComboName.IsEqual(NAME_None))
	{
		return;
	}
	
	UAnimInstance* OwnerAnimInstance = GetOwnerAnimInstance();
	if (!IsValid(OwnerAnimInstance)) return;
	OwnerAnimInstance->Montage_SetNextSection(OwnerAnimInstance->Montage_GetCurrentSection(), NextComboName);
}

void UGA_Combo::DoDamage(FGameplayEventData Data)
{
	TArray<FHitResult> HitResults = GetHitResultFromSweepLocationTargetData(Data.TargetData, TargetSweepSphere);
	
	for (const FHitResult& HitResult : HitResults)
	{
		const TSubclassOf<UGameplayEffect> GameplayEffect = GetDamageEffectForCurrentCombo();
		
		const float Level = GetAbilityLevel(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo());
		
		FGameplayEffectContextHandle EffectContextHandle = MakeEffectContext(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo());
		EffectContextHandle.AddHitResult(HitResult);
		
		const FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(GameplayEffect, Level);
		EffectSpecHandle.Data->SetContext(EffectContextHandle);
		
		ApplyGameplayEffectSpecToTarget(GetCurrentAbilitySpecHandle(), CurrentActorInfo, CurrentActivationInfo, EffectSpecHandle, UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(HitResult.GetActor()));
	}
}

TSubclassOf<UGameplayEffect> UGA_Combo::GetDamageEffectForCurrentCombo() const
{
	const UAnimInstance* OwnerAnimInstance = GetOwnerAnimInstance();
	if (!IsValid(OwnerAnimInstance)) return nullptr;
	
	const FName CurrentComboName = OwnerAnimInstance->Montage_GetCurrentSection(ComboMontage);
	
	const TSubclassOf<UGameplayEffect>* FoundEffectPtr = DamageEffectMap.Find(CurrentComboName);
	
	if (!IsValid(*FoundEffectPtr))
	{
		return DefaultDamageEffect;
	}
	
	return *FoundEffectPtr;
}
