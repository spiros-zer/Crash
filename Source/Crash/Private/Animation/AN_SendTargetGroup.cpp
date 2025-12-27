// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_SendTargetGroup.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

void UAN_SendTargetGroup::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	if (!IsValid(MeshComp)) return;

	AActor* Owner = MeshComp->GetOwner();
	
	if (!IsValid(Owner)) return;
	
	// Sweep requires always 2 positions
	
	if (TargetSocketNames.Num() < 1) return;

	UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Owner);
	if (!IsValid(AbilitySystemComponent)) return;
	
	// Adding socket locations to the gameplay event data
	
	FGameplayEventData Data;
	
	// Staring from 1 since start location will be at position 0 and end location will be at 1
	
	for (int Index = 1; Index < TargetSocketNames.Num(); Index++)
	{
		// Heap allocation. This is converted to a shared ptr internally in FGameplayAbilityTargetDataHandle::Add
		
		FVector StartLocation = MeshComp->GetSocketLocation(TargetSocketNames[Index - 1]);
		
		FVector EndLocation = MeshComp->GetSocketLocation(TargetSocketNames[Index]);
		
		FGameplayAbilityTargetData_LocationInfo* LocationInfo = new FGameplayAbilityTargetData_LocationInfo();
		check(LocationInfo);
		LocationInfo->SourceLocation.LiteralTransform.SetLocation(StartLocation);
		LocationInfo->TargetLocation.LiteralTransform.SetLocation(EndLocation);
		
		Data.TargetData.Add(LocationInfo);
	}
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Owner, EventTag, Data);
}
