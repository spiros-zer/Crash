// Fill out your copyright notice in the Description page of Project Settings.


#include "CCharacter.h"

#include "Components/WidgetComponent.h"
#include "GAS/CAbilitySystemComponent.h"
#include "GAS/CAttributeSet.h"
#include "Widgets/OverheadStatusGauge.h"


// Sets default values
ACCharacter::ACCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	CAbilitySystemComponent = CreateDefaultSubobject<UCAbilitySystemComponent>("CAbilitySystemComponent");
	check(CAbilitySystemComponent);
	
	CAttributeSet = CreateDefaultSubobject<UCAttributeSet>("CAttributeSet");
	check(CAttributeSet);
	
	OverheadWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("OverheadWidgetComponent");
	check(OverheadWidgetComponent);
	OverheadWidgetComponent->SetupAttachment(GetRootComponent());
}

void ACCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	ConfigureOverheadStatusWidget();
}

void ACCharacter::ServerSideInit()
{
	CAbilitySystemComponent->InitAbilityActorInfo(this, this);
	CAbilitySystemComponent->ApplyInitialEffects();
}

void ACCharacter::ClientSideInit()
{
	CAbilitySystemComponent->InitAbilityActorInfo(this, this);
}

UAbilitySystemComponent* ACCharacter::GetAbilitySystemComponent() const
{
	return CAbilitySystemComponent;
}

void ACCharacter::ConfigureOverheadStatusWidget()
{
	UOverheadStatusGauge* OverheadStatusGauge = Cast<UOverheadStatusGauge>(OverheadWidgetComponent->GetUserWidgetObject());
	check(OverheadStatusGauge);
	
	OverheadStatusGauge->ConfigureWithAsc(GetAbilitySystemComponent());
}

