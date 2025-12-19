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
	
	void ServerSideInit();
	
	void ClientSideInit();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
private:
	
	UPROPERTY(VisibleDefaultsOnly, Category = "AbilitySystem")
	TObjectPtr<UCAbilitySystemComponent> CAbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UCAttributeSet> CAttributeSet;
};
