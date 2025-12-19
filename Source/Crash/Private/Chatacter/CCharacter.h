// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "CCharacter.generated.h"

class UCAttributeSet;
class UCAbilitySystemComponent;

UCLASS()
class CRASH_API ACCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACCharacter();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
private:
	
	UPROPERTY()
	TObjectPtr<UCAbilitySystemComponent> CAbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UCAttributeSet> CAttributeSet;
};
