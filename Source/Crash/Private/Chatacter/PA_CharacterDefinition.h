// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PA_CharacterDefinition.generated.h"

class ACCharacter;
/**
 * 
 */
UCLASS()
class CRASH_API UPA_CharacterDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
	
	static FPrimaryAssetType GetCharacterDefinitionAssetType();
	
	FString GetCharacterDisplayName() const;
	
	UTexture2D* LoadIcon() const;
	
	TSubclassOf<ACCharacter> LoadCharacterClass() const;
	
	TSubclassOf<UAnimInstance> LoadDisplayAnimBPClass() const;
	
	USkeletalMesh* LoadDisplayMesh() const;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Character")
	FString CharacterName;
	
	UPROPERTY(EditDefaultsOnly, Category = "Character")
	TSoftObjectPtr<UTexture2D> CharacterIcon;
	
	UPROPERTY(EditDefaultsOnly, Category = "Character")
	TSoftClassPtr<ACCharacter> CharacterClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Character")
	TSoftClassPtr<UAnimInstance> DisplayAnimBPClass;
};
