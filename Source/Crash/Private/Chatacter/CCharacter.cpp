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
	
	
	// Disabling the collision here might not reflect in the child classes. Make sure this is reflected in BP.
	
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
	
	MeshRelativeTransform = GetMesh()->GetRelativeTransform();
	
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
	
	SetRagdollEnabled(false);
	
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	
	// Since auto blend out is fals for the death anim montage, need to  manually stop it here
	
	GetMesh()->GetAnimInstance()->StopAllMontages(0.f);
	
	SetStatusGaugeEnabled(true);
	
	if (!IsValid(CAbilitySystemComponent)) return;
	CAbilitySystemComponent->ApplyFullStatEffect();
}

void ACCharacter::PlayDeathAnimation()
{
	check(DeathMontage);
	
	const float MontageDuration = PlayAnimMontage(DeathMontage);
	
	// Turn to ragdoll physics a little earlier from the DeathMontage's finish. This makes the transition smoother.
	
	GetWorldTimerManager().SetTimer(DeathMontageTimerHandle, this, &ThisClass::DeathMontageFinished, MontageDuration + DeathMontageFinishTimeShift);
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

void ACCharacter::DeathMontageFinished()
{
	// SetRagdollEnabled(true); Disabled ragdoll physics
}

void ACCharacter::SetRagdollEnabled(bool bIsEnabled)
{
	if (bIsEnabled)
	{
		GetMesh()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		GetMesh()->SetSimulatePhysics(true);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	}
	{
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetMesh()->SetSimulatePhysics(false);
		GetMesh()->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		GetMesh()->SetRelativeTransform(MeshRelativeTransform);
	}
}
