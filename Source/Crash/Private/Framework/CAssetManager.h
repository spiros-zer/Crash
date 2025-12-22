// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "CAssetManager.generated.h"

class UPA_CharacterDefinition;
/**
 * 
 */
UCLASS()
class CRASH_API UCAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	
	static UCAssetManager& Get();
	
	void LoadCharacterDefinitions(const FStreamableDelegate& LoadFinishedCallback);
	
	/** 
	 * Call when LoadCharacterDefinitions has finished loading.
	 */
	bool GetLoadedCharacterDefinitions(TArray<UPA_CharacterDefinition*>& LoadedCharacterDefinitions) const;
};
