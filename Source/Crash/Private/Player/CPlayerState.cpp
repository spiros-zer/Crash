// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayerState.h"

#include "Chatacter/PA_CharacterDefinition.h"
#include "Framework/CGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

ACPlayerState::ACPlayerState()
{
	// Network settings
	
	bReplicates = true;
	
	SetNetUpdateFrequency(100.f);
}

void ACPlayerState::BeginPlay()
{
	Super::BeginPlay();
	
	CGameState = Cast<ACGameState>(UGameplayStatics::GetGameState(this));
	if(!IsValid(CGameState)) return;
	CGameState->OnPlayerSelectionUpdated.AddUObject(this, &ThisClass::PlayerSelectionUpdated);
}

void ACPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, PlayerSelection);
}

void ACPlayerState::Server_SetSelectedCharacterDefinition_Implementation(const UPA_CharacterDefinition* NewDefinition)
{
	if (!IsValid(CGameState)) return;
	
	if (!IsValid(NewDefinition)) return;
	
	if (CGameState->IsDefinitionSelected(NewDefinition)) return;

	// Deselect previously selected character

	if (const UPA_CharacterDefinition* SelectedCharacterDefinition = PlayerSelection.GetCharacterDefinition())
	{
		CGameState->SetCharacterDeselected(SelectedCharacterDefinition);
	}
	
	PlayerSelection.SetCharacterDefinition(NewDefinition);
	
	CGameState->SetCharacterSelected(this, NewDefinition);
}

bool ACPlayerState::Server_SetSelectedCharacterDefinition_Validate(const UPA_CharacterDefinition* NewDefinition)
{
	return true;
}

void ACPlayerState::PlayerSelectionUpdated(const TArray<FPlayerSelection>& NewPlayerSelections)
{
	for (const FPlayerSelection& NewPlayerSelection : NewPlayerSelections)
	{
		if (!NewPlayerSelection.IsForPlayer(this)) continue;
		
		PlayerSelection = NewPlayerSelection;
	}
}
