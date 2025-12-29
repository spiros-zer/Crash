// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayerController.h"

#include "CPlayerCharacter.h"
#include "Net/UnrealNetwork.h"
#include "Widgets/GameplayWidget.h"

void ACPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	CPlayerCharacter = Cast<ACPlayerCharacter>(InPawn);
	if (!IsValid(CPlayerCharacter)) return;
	CPlayerCharacter->ServerSideInit();
	CPlayerCharacter->SetGenericTeamId(TeamId);
}

void ACPlayerController::AcknowledgePossession(APawn* InPawn)
{
	Super::AcknowledgePossession(InPawn);
	
	CPlayerCharacter = Cast<ACPlayerCharacter>(InPawn);
	if (!IsValid(CPlayerCharacter)) return;
	CPlayerCharacter->ClientSideInit();
	
	// This also executes for the listen server as well.
	
	SpawnGameplayWidget();
}

void ACPlayerController::SpawnGameplayWidget()
{
	check(GameplayWidgetClass);
	
	// Spawn the widget if we are on a local machine.
	
	if (!IsLocalPlayerController()) return;
	
	GameplayWidget = CreateWidget<UGameplayWidget>(this, GameplayWidgetClass);
	
	if (GameplayWidget)
	{
		GameplayWidget->AddToViewport();
	}
}

void ACPlayerController::SetGenericTeamId(const FGenericTeamId& InTeamID)
{
	TeamId = InTeamID;
}

FGenericTeamId ACPlayerController::GetGenericTeamId() const
{
	return TeamId;
}

void ACPlayerController::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, TeamId);
}
