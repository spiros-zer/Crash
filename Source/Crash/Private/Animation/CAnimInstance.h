// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance.generated.h"

class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class CRASH_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	
	UFUNCTION(BlueprintGetter, meta = (BlueprintThreadSafe))
	FORCEINLINE bool GetIsJumping() const;
	
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	FORCEINLINE bool GetIsGrounded() const;
	
	UFUNCTION(BlueprintGetter, meta = (BlueprintThreadSafe))
	FORCEINLINE float GetSpeed() const;
	
	UFUNCTION(BlueprintGetter, meta = (BlueprintThreadSafe))
	FORCEINLINE float GetYawSpeed() const;
	
	UFUNCTION(BlueprintGetter, meta = (BlueprintThreadSafe))
	FORCEINLINE float GetSmoothedYawSpeed() const;
	
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	FORCEINLINE bool IsMoving() const;
	
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	FORCEINLINE bool IsNotMoving() const;
	
private:
	
	UPROPERTY()
	TObjectPtr<ACharacter> OwnerCharacter;
	
	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> OwnerMovementComponent;
	
	UPROPERTY(BlueprintGetter = GetIsJumping)
	bool bIsJumping = false;
	
	UPROPERTY(BlueprintGetter = GetSpeed)
	float Speed = 0;
	
	UPROPERTY(BlueprintGetter = GetYawSpeed)
	float YawSpeed = 0;
	
	UPROPERTY(BlueprintGetter = GetSmoothedYawSpeed)
	float SmoothedYawSpeed = 0;
	
	UPROPERTY(EditAnywhere, Category = "Animation")
	float YawSpeedSmoothLerpSpeed = 1.f;
	
	FRotator BodyPreviousRotation;
};
