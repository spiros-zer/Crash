// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInfoTypes.h"

#include "GameFramework/PlayerState.h"
#include "Network/CNetStatics.h"

FPlayerSelection::FPlayerSelection() : SlotID{GetInvalidSlotID()}, PlayerUniqueID{FUniqueNetIdRepl::Invalid()}, PlayerNickName{}
{
}

FPlayerSelection::FPlayerSelection(uint8 InSlotId, const APlayerState* InPlayerState) : SlotID{InSlotId}
{
	if (!IsValid(InPlayerState)) return;
	
	PlayerUniqueID = InPlayerState->GetUniqueId();
	
	PlayerNickName = InPlayerState->GetPlayerName();
}

uint8 FPlayerSelection::GetInvalidSlotID()
{
	return 255;
}

uint8 FPlayerSelection::GetSlotID() const
{
	return SlotID;
}

void FPlayerSelection::SetSlotID(uint8 InSlotID)
{
	SlotID = InSlotID;
}

const FUniqueNetIdRepl& FPlayerSelection::GetPlayerUniqueID() const
{
	return PlayerUniqueID;
}

const FString& FPlayerSelection::GetPlayerNickName() const
{
	return PlayerNickName;
}

bool FPlayerSelection::IsForPlayer(const APlayerState* InPlayerState) const
{
	if (!IsValid(InPlayerState))
	{
		return false;
	}
	
#if WITH_EDITOR
	return InPlayerState->GetPlayerName() == PlayerNickName;
#else
	return PlayerState->GetUniqueId() == GetPlayerUniqueID();
#endif
}

bool FPlayerSelection::IsPlayerSelectionValid() const
{
#if WITH_EDITOR
	return true;
#else
	if (!PlayerUniqueID.IsValid())
	{
		return false;
	}
	
	if (SlotID == GetInvalidSlotID())
	{
		return false;
	}
	
	if (SlotID >= UCNetStatics::GetPlayerCountPerTeam())
	{
		return false;
	}
	
	return true;
#endif
}
