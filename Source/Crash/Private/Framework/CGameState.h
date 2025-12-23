// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Player/PlayerInfoTypes.h"
#include "CGameState.generated.h"

class UPA_CharacterDefinition;
/**
 * 
 */
UCLASS()
class CRASH_API ACGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	void RequestPlayerSelectionChange(const APlayerState* RequestingPlayer, uint8 DesiredSlot);
	
	void SetCharacterSelected(const APlayerState* SelectingPlayer, const UPA_CharacterDefinition* SelectedDefinition);
	
	void SetCharacterDeselected(const UPA_CharacterDefinition* DefinitionToDeselect);
	
	/** 
	 * Returns whether the game can proceed to the hero selection. 
	 */
	bool CanStartHeroSelection() const;
	
	bool IsSlotOccupied(uint8 SlotID) const;
	
	bool IsDefinitionSelected(const UPA_CharacterDefinition* Definition) const;
	
	const TArray<FPlayerSelection>& GetPlayerSelectionArray() const;
	
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerSelectionUpdatedSignature, const TArray<FPlayerSelection>& /** NewPlayerSelection */)
	FOnPlayerSelectionUpdatedSignature OnPlayerSelectionUpdated;
	
private:
	
	UFUNCTION()
	void OnRep_PlayerSelectionArray();
	
	UPROPERTY(ReplicatedUsing = OnRep_PlayerSelectionArray)
	TArray<FPlayerSelection> PlayerSelectionArray;
};
