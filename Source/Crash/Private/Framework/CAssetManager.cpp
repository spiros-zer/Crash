// Fill out your copyright notice in the Description page of Project Settings.


#include "CAssetManager.h"

#include "Chatacter/PA_CharacterDefinition.h"

UCAssetManager& UCAssetManager::Get()
{
	UCAssetManager* Singleton = Cast<UCAssetManager>(GEngine->AssetManager.Get());
	if (!Singleton)
	{
		UE_LOG(LogTemp, Fatal, TEXT("AssetManager needs to be of type CAssetManager."));
	}
	
	return *Singleton;
}

void UCAssetManager::LoadCharacterDefinitions(const FStreamableDelegate& LoadFinishedCallback)
{
	LoadPrimaryAssetsWithType(UPA_CharacterDefinition::GetCharacterDefinitionAssetType(), TArray<FName>(), LoadFinishedCallback);
}

bool UCAssetManager::GetLoadedCharacterDefinitions(TArray<UPA_CharacterDefinition*>& LoadedCharacterDefinitions) const
{
	TArray<UObject*> LoadedObjects;
	
	bool bLoaded = GetPrimaryAssetObjectList(UPA_CharacterDefinition::GetCharacterDefinitionAssetType(), LoadedObjects);
	if (bLoaded)
	{
		for (UObject* Object : LoadedObjects)
		{
			LoadedCharacterDefinitions.Add(Cast<UPA_CharacterDefinition>(Object));
		}
	}
		
	return bLoaded;
}
