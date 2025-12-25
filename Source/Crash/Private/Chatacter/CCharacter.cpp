// Fill out your copyright notice in the Description page of Project Settings.


#include "CCharacter.h"

#include "Components/WidgetComponent.h"
#include "GAS/CAbilitySystemComponent.h"
#include "GAS/CAttributeSet.h"
#include "Widgets/OverheadStatusGauge.h"


ACCharacter::ACCharacter()
{
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

void ACCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	// Called only on server.
	
	// Server side init for AIControllers.
	
	if (NewController && !NewController->IsPlayerController())
	{
		ServerSideInit();
	}
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
	// Don't show the widget component for own player's character
	
	if (IsLocallyControlled())
	{
		OverheadWidgetComponent->SetHiddenInGame(true);
		
		return;
	}
	
	UOverheadStatusGauge* OverheadStatusGauge = Cast<UOverheadStatusGauge>(OverheadWidgetComponent->GetUserWidgetObject());
	check(OverheadStatusGauge);
	
	OverheadStatusGauge->ConfigureWithAsc(GetAbilitySystemComponent());
}

