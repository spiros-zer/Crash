// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Crash/Private/Chatacter/CCharacter.h"
#include "CPlayerCharacter.generated.h"

class UInputAction;
class UInputMappingContext;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class CRASH_API ACPlayerCharacter : public ACCharacter
{
	GENERATED_BODY()
	
public:
	
	ACPlayerCharacter();
	
	virtual void PawnClientRestart() override;
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	
	UPROPERTY(VisibleDefaultsOnly, Category = "View")
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "View")
	TObjectPtr<UCameraComponent> ViewCamera;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> JumpInputAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> GameplayInputMappingContext;
};
