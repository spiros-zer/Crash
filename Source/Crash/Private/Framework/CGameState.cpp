// Fill out your copyright notice in the Description page of Project Settings.


#include "CGameState.h"

#include "Net/UnrealNetwork.h"

void ACGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, PlayerSelectionArray, COND_None, REPNOTIFY_Always)
}

void ACGameState::RequestPlayerSelectionChange(const APlayerState* RequestingPlayer, uint8 DesiredSlot)
{
	if (!HasAuthority() || IsSlotOccupied(DesiredSlot)) return;
	
	FPlayerSelection* PlayerSelectionPtr = PlayerSelectionArray.FindByPredicate([&](const FPlayerSelection& PlayerSelection)
	{
		return PlayerSelection.IsForPlayer(RequestingPlayer);
	});
	
	if (PlayerSelectionPtr)
	{
		PlayerSelectionPtr->SetSlotID(DesiredSlot);
	}
	else
	{
		PlayerSelectionArray.Add(FPlayerSelection(DesiredSlot, RequestingPlayer));
	}
	
	OnPlayerSelectionUpdated.Broadcast(PlayerSelectionArray);
}

void ACGameState::SetCharacterSelected(const APlayerState* SelectingPlayer, const UPA_CharacterDefinition* SelectedDefinition)
{
	if (IsDefinitionSelected(SelectedDefinition)) return;
	
	FPlayerSelection* FoundPlayerSelection = PlayerSelectionArray.FindByPredicate([&](const FPlayerSelection& PlayerSelection)
	{
		return PlayerSelection.IsForPlayer(SelectingPlayer);
	});
	
	check(FoundPlayerSelection);
	
	FoundPlayerSelection->SetCharacterDefinition(SelectedDefinition);
	
	OnPlayerSelectionUpdated.Broadcast(PlayerSelectionArray);
}

void ACGameState::SetCharacterDeselected(const UPA_CharacterDefinition* DefinitionToDeselect)
{
	check(DefinitionToDeselect);
	
	FPlayerSelection* FoundPlayerSelection = PlayerSelectionArray.FindByPredicate([&](const FPlayerSelection& PlayerSelection)
	{
		return PlayerSelection.GetCharacterDefinition() == DefinitionToDeselect;
	});
	
	check(FoundPlayerSelection);
	
	FoundPlayerSelection->SetCharacterDefinition(nullptr);
	
	OnPlayerSelectionUpdated.Broadcast(PlayerSelectionArray);
}

bool ACGameState::CanStartHeroSelection() const
{
	// return whether the players with selections are as many as the players.
	
	return PlayerSelectionArray.Num() == PlayerArray.Num();
}

bool ACGameState::IsSlotOccupied(uint8 SlotID) const
{
	for (const FPlayerSelection& PlayerSelection : PlayerSelectionArray)
	{
		if (PlayerSelection.GetSlotID() == SlotID)
		{
			return true;
		}
	}
	
	return false;
}

bool ACGameState::IsDefinitionSelected(const UPA_CharacterDefinition* Definition) const
{
	const FPlayerSelection* FoundPlayerSelection = PlayerSelectionArray.FindByPredicate([&](const FPlayerSelection& PlayerSelection)
	{
		return PlayerSelection.GetCharacterDefinition() == Definition;
	});
	
	return FoundPlayerSelection != nullptr;
}

const TArray<FPlayerSelection>& ACGameState::GetPlayerSelectionArray() const
{
	return PlayerSelectionArray;
}

void ACGameState::OnRep_PlayerSelectionArray()
{
	OnPlayerSelectionUpdated.Broadcast(PlayerSelectionArray);
}
