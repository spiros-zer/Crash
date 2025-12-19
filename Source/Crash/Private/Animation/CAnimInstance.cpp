// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimInstance.h"

#include "GameFramework/Character.h"

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
}

void UCAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

float UCAnimInstance::GetSpeed() const
{
	return Speed;
}

bool UCAnimInstance::IsMoving() const
{
	return Speed != 0.f;
}

bool UCAnimInstance::IsNotMoving() const
{
	return Speed == 0.f;
}
