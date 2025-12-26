// Fill out your copyright notice in the Description page of Project Settings.


#include "CGameplayAbility.h"

TObjectPtr<UAnimInstance> UCGameplayAbility::GetOwnerAnimInstance() const
{
	const USkeletalMeshComponent* OwnerSkeletalMeshComponent = GetOwningComponentFromActorInfo();
	if (!IsValid(OwnerSkeletalMeshComponent))
	{
		return nullptr;
	}
	
	return OwnerSkeletalMeshComponent->GetAnimInstance();
}
