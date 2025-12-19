// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimInstance.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UCAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
	if (!IsValid(OwnerCharacter)) return;
	
	OwnerMovementComponent = OwnerCharacter->GetCharacterMovement();
	check(OwnerMovementComponent);
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (!IsValid(OwnerCharacter)) return;
	
	Speed = OwnerCharacter->GetVelocity().Length();

	const FRotator BodyRotation = OwnerCharacter->GetActorRotation();

	const FRotator BodyRotDelta = UKismetMathLibrary::NormalizedDeltaRotator(BodyRotation, BodyPreviousRotation);
	
	YawSpeed = BodyRotDelta.Yaw / DeltaSeconds;
	
	BodyPreviousRotation = BodyRotation;
	
	SmoothedYawSpeed = UKismetMathLibrary::FInterpTo(SmoothedYawSpeed, YawSpeed, DeltaSeconds, YawSpeedSmoothLerpSpeed);
	
	FRotator ControlRot = OwnerCharacter->GetBaseAimRotation();
	
	LookRotOffset = UKismetMathLibrary::NormalizedDeltaRotator(ControlRot, BodyRotation);
	
	if (!IsValid(OwnerMovementComponent)) return;

	bIsJumping = OwnerMovementComponent->IsFalling();
}

void UCAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

bool UCAnimInstance::GetIsJumping() const
{
	return bIsJumping;
}

bool UCAnimInstance::GetIsGrounded() const
{
	return !bIsJumping;
}

float UCAnimInstance::GetSpeed() const
{
	return Speed;
}

float UCAnimInstance::GetYawSpeed() const
{
	return YawSpeed;
}

float UCAnimInstance::GetSmoothedYawSpeed() const
{
	return SmoothedYawSpeed;
}

float UCAnimInstance::GetLookYawOffset() const
{
	return LookRotOffset.Yaw;
}

float UCAnimInstance::GetLookPitchOffset() const
{
	return LookRotOffset.Pitch;
}

bool UCAnimInstance::IsMoving() const
{
	return Speed != 0.f;
}

bool UCAnimInstance::IsNotMoving() const
{
	return Speed == 0.f;
}
