// Fill out your copyright notice in the Description page of Project Settings.


#include "CCharacter.h"

#include "GAS/CAbilitySystemComponent.h"
#include "GAS/CAttributeSet.h"


// Sets default values
ACCharacter::ACCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	CAbilitySystemComponent = CreateDefaultSubobject<UCAbilitySystemComponent>("CAbilitySystemComponent");
	
	CAttributeSet = CreateDefaultSubobject<UCAttributeSet>("CAttributeSet");
}

UAbilitySystemComponent* ACCharacter::GetAbilitySystemComponent() const
{
	return CAbilitySystemComponent;
}

