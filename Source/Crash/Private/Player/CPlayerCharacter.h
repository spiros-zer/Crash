// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Crash/Private/Chatacter/CCharacter.h"
#include "GAS/CGameplayAbilityTypes.h"
#include "CPlayerCharacter.generated.h"

struct FInputActionValue;
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
	
protected:
	
	virtual void OnDeath() override;
	
	virtual void OnRespawn() override;

private:
	
	void HandleLookInput(const FInputActionValue& InputActionValue);
	
	void HandleMoveInput(const FInputActionValue& InputActionValue);
	
	/** 
	 * Returns the right direction. This is both for Look and Move.
	 */
	FVector GetLookRightDir() const;
	
	/** 
	 * Returns the look direction. Can be any arbitraty direction (Up, Down, etc.).
	 */
	FVector GetLookFwdDir() const;
	
	/** 
	 * Returns the move direction. The difference with the LookFwd is that we cannot move in all the directions (cannot
	 * go directly Up, Down, etc.).
	 */
	FVector GetMoveFwdDir() const;
	
	void HandleAbilityInput(const FInputActionValue& InputActionValue, ECAbilityInputID InputID);
	
	UPROPERTY(VisibleDefaultsOnly, Category = "View")
	TObjectPtr<UCameraComponent> ViewCamera;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "View")
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TMap<ECAbilityInputID, TObjectPtr<UInputAction>> GameplayAbilityInputActions;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> JumpInputAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> LookInputAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveInputAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> GameplayInputMappingContext;
};
