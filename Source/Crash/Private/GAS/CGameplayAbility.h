// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "CGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class CRASH_API UCGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
protected:
	
	TObjectPtr<UAnimInstance> GetOwnerAnimInstance() const;
};
