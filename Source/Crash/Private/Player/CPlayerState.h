// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerInfoTypes.h"
#include "GameFramework/PlayerState.h"
#include "CPlayerState.generated.h"

class ACGameState;
/**
 * 
 */
UCLASS()
class CRASH_API ACPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	
	ACPlayerState();

	virtual void BeginPlay() override;
	
	virtual void CopyProperties(APlayerState* PlayerState) override;
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SetSelectedCharacterDefinition(const UPA_CharacterDefinition* NewDefinition);
	
	TSubclassOf<APawn> GetSelectedPawnClass() const;
	
private:
	
	void PlayerSelectionUpdated(const TArray<FPlayerSelection>& NewPlayerSelections);
	
	UPROPERTY(Replicated)
	FPlayerSelection PlayerSelection;
	
	UPROPERTY()
	TObjectPtr<ACGameState> CGameState;
};
