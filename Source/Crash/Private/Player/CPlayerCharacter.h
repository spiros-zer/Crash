// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Crash/Private/Chatacter/CCharacter.h"
#include "CPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class CRASH_API ACPlayerCharacter : public ACCharacter
{
	GENERATED_BODY()
	
public:
	
	ACPlayerCharacter();

private:
	
	UPROPERTY(VisibleDefaultsOnly, Category = "View")
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "View")
	TObjectPtr<UCameraComponent> ViewCamera;
};
