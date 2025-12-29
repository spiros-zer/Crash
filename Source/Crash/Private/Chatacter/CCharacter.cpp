// Fill out your copyright notice in the Description page of Project Settings.


#include "CCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/CAbilitySystemComponent.h"
#include "GAS/CAttributeSet.h"
#include "GAS/CTags.h"
#include "Kismet/GameplayStatics.h"
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
	
	BindGASChangeDelegates();
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
	CAbilitySystemComponent->GiveInitialAbilities();
}

void ACCharacter::ClientSideInit()
{
	CAbilitySystemComponent->InitAbilityActorInfo(this, this);
}

UAbilitySystemComponent* ACCharacter::GetAbilitySystemComponent() const
{
	return CAbilitySystemComponent;
}

void ACCharacter::OnDeath()
{
}

void ACCharacter::OnRespawn()
{
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
	
	// Setup the OverheadStatusGauge visibility timer.
	
	GetWorldTimerManager().ClearTimer(OverheadStatusGaugeVisibilityTimerHandle);
	GetWorldTimerManager().SetTimer(OverheadStatusGaugeVisibilityTimerHandle, this, &ThisClass::UpdateOverheadStatusGaugeVisibility, OverheadStatusGaugeVisibilityCheckUpdateGap, true);
}

void ACCharacter::UpdateOverheadStatusGaugeVisibility()
{
	APawn* LocalPlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (!IsValid(LocalPlayerPawn)) return;
	
	float DistSquared = FVector::DistSquared(GetActorLocation(), LocalPlayerPawn->GetActorLocation());
	
	OverheadWidgetComponent->SetHiddenInGame(DistSquared >= OverheadStatusGaugeVisibilityRangeSquared);
}

void ACCharacter::BindGASChangeDelegates()
{
	if (!IsValid(CAbilitySystemComponent)) return;
	
	CAbilitySystemComponent->RegisterGameplayTagEvent(Stats::Dead).AddUObject(this, &ThisClass::DeathTagUpdated);
}

void ACCharacter::DeathTagUpdated(FGameplayTag GameplayTag, int NewCount)
{
	if (NewCount != 0)
	{
		StartDeathSequence();
	}
	else
	{
		Respawn();
	}
}

void ACCharacter::StartDeathSequence()
{
	OnDeath();
	
	PlayDeathAnimation();
	
	SetStatusGaugeEnabled(false);
	
	GetCharacterMovement()->SetMovementMode(MOVE_None);
	
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACCharacter::Respawn()
{
	OnRespawn();
}

void ACCharacter::PlayDeathAnimation()
{
	check(DeathMontage);
	
	PlayAnimMontage(DeathMontage);
}

void ACCharacter::SetStatusGaugeEnabled(bool bIsEnabled)
{
	GetWorldTimerManager().ClearTimer(OverheadStatusGaugeVisibilityTimerHandle);
	
	if (bIsEnabled)
	{
		ConfigureOverheadStatusWidget();
	}
	else
	{
		OverheadWidgetComponent->SetHiddenInGame(true);
	}
}
