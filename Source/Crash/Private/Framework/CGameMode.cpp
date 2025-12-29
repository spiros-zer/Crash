// Fill out your copyright notice in the Description page of Project Settings.


#include "CGameMode.h"

#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"

APlayerController* ACGameMode::SpawnPlayerController(ENetRole InRemoteRole, const FString& Options)
{
	APlayerController* PlayerController = Super::SpawnPlayerController(InRemoteRole, Options);
	check(PlayerController);
	
	const FGenericTeamId TeamId = GetTeamIdForPlayer(PlayerController);

	if (IGenericTeamAgentInterface* NewPlayerTeamInterface = Cast<IGenericTeamAgentInterface>(PlayerController))
	{
		NewPlayerTeamInterface->SetGenericTeamId(TeamId);
	}	
	
	PlayerController->StartSpot = FindNextStartSpotForTeam(TeamId);
	
	return PlayerController;
}

FGenericTeamId ACGameMode::GetTeamIdForPlayer(const APlayerController* InPlayerController) const
{
	static int PlayerCount = 0;
	++PlayerCount;
	
	return FGenericTeamId(PlayerCount % 2);
}

AActor* ACGameMode::FindNextStartSpotForTeam(const FGenericTeamId InTeamId)
{
	const FName* StartSpotTag = TeamStartSpotTagMap.Find(InTeamId);
	if (!StartSpotTag) return nullptr;
	
	const UWorld* World = GetWorld();
	check(World);

	for (TActorIterator<APlayerStart> PlayerStart(World); PlayerStart; ++PlayerStart) 
	{
		if (PlayerStart->PlayerStartTag == *StartSpotTag)
		{
			// Mark as occupied to avoid players spawning on it
			PlayerStart->PlayerStartTag = FName("Taken");
			
			return *PlayerStart;
		}
	}
	
	return nullptr;
}
