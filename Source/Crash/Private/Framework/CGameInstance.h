// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CRASH_API UCGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	
	void StartMatch();
	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Map")
	TSoftObjectPtr<UWorld> MainMenuLevel;
	
	UPROPERTY(EditDefaultsOnly, Category = "Map")
	TSoftObjectPtr<UWorld> LobbyLevel;
	
	UPROPERTY(EditDefaultsOnly, Category = "Map")
	TSoftObjectPtr<UWorld> GameLevel;
	
private:
	
	void LoadLevelAndListen(TSoftObjectPtr<UWorld> Level);
};
