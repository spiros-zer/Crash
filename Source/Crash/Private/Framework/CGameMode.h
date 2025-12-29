// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/GameModeBase.h"
#include "CGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CRASH_API ACGameMode : public AGameModeBase, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
public:
	
	/** 
	 * Called when the player is to be spawned (locally or multiplayer) and before the pawn is spawned.
	 */
	virtual APlayerController* SpawnPlayerController(ENetRole InRemoteRole, const FString& Options) override;
	
protected:
	
	/** 
	 * Holds the team id to a player start tag.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Team")
	TMap<FGenericTeamId, FName> TeamStartSpotTagMap;
	
private:
	
	FGenericTeamId GetTeamIdForPlayer(const APlayerController* InPlayerController) const;
	
	AActor* FindNextStartSpotForTeam(const FGenericTeamId InTeamId);
};
