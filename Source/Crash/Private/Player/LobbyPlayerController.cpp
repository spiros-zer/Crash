// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyPlayerController.h"
#include "GameFramework/PlayerState.h"

#include "Framework/CGameState.h"

ALobbyPlayerController::ALobbyPlayerController()
{
	// Disable automatic camera activation.
	
	bAutoManageActiveCameraTarget = false;
}

void ALobbyPlayerController::Server_RequestSlotSelectionChange_Implementation(uint8 NewSlotID)
{
	const UWorld* World = GetWorld();
	if (!IsValid(World)) return;
	
	ACGameState* CGameState = World->GetGameState<ACGameState>();
	if (!IsValid(CGameState)) return;
	CGameState->RequestPlayerSelectionChange(GetPlayerState<APlayerState>(), NewSlotID);
}

bool ALobbyPlayerController::Server_RequestSlotSelectionChange_Validate(uint8 NewSlotID)
{
	return true;
}

void ALobbyPlayerController::Server_StartHeroSelection_Implementation()
{
	if (!HasAuthority()) return;
	
	const UWorld* World = GetWorld();
	if (!IsValid(World)) return;
	
	for (FConstPlayerControllerIterator PlayerControllerIterator = GetWorld()->GetPlayerControllerIterator(); PlayerControllerIterator; ++PlayerControllerIterator)
	{
		ALobbyPlayerController* PlayerController = Cast<ALobbyPlayerController>(*PlayerControllerIterator);
		if (!IsValid(PlayerController)) return;
		PlayerController->Client_StartHeroSelection();
	}
}

bool ALobbyPlayerController::Server_StartHeroSelection_Validate()
{
	return true;
}

void ALobbyPlayerController::Client_StartHeroSelection_Implementation()
{
	SwitchToHeroSelection.ExecuteIfBound();
}
