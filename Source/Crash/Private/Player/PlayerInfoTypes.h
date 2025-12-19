// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "PlayerInfoTypes.generated.h"

class APlayerState;

/** 
 * Package to keep track of player selection info
 */
USTRUCT()
struct FPlayerSelection
{
	GENERATED_BODY()
	
	FPlayerSelection();
	
	FPlayerSelection(uint8 InSlotId, const APlayerState* InPlayerState);
	
	static uint8 GetInvalidSlotID();
	
	FORCEINLINE uint8 GetSlotID() const;
	
	FORCEINLINE void SetSlotID(uint8 InSlotID);
	
	FORCEINLINE const FUniqueNetIdRepl& GetPlayerUniqueID() const;
	
	FORCEINLINE const FString& GetPlayerNickName() const;
	
	bool IsForPlayer(const APlayerState* InPlayerState) const;
	
	bool IsPlayerSelectionValid() const;
	
private:
	
	UPROPERTY()
	uint8 SlotID;
	
	/** 
	 * An internal ID that can be replicated. Determines what a specific player selects.
	 */
	UPROPERTY()
	FUniqueNetIdRepl PlayerUniqueID;
	
	UPROPERTY()
	FString PlayerNickName;
};
