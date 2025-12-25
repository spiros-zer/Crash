// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_SendGameplayEvent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagsManager.h"

void UAN_SendGameplayEvent::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	check(MeshComp->GetOwner());
	
	const UAbilitySystemComponent* Asc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(MeshComp->GetOwner());
	if (!IsValid(Asc)) return; 
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComp->GetOwner(), EventTag, FGameplayEventData());
}

FString UAN_SendGameplayEvent::GetNotifyName_Implementation() const
{
	if (!EventTag.IsValid())
	{
		return "None";
	}
	
	// Split Tag into parts and return the last part since that contains the info we need.
	
	TArray<FName> TagNames;
	
	UGameplayTagsManager::Get().SplitGameplayTagFName(EventTag, TagNames);
	
	return TagNames.Last().ToString();
	
}
