// Fill out your copyright notice in the Description page of Project Settings.


#include "PA_CharacterDefinition.h"

#include "CCharacter.h"

FPrimaryAssetId UPA_CharacterDefinition::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(GetCharacterDefinitionAssetType(), GetFName());
}

FPrimaryAssetType UPA_CharacterDefinition::GetCharacterDefinitionAssetType()
{
	return FPrimaryAssetType("CharacterDefinition");
}

FString UPA_CharacterDefinition::GetCharacterDisplayName() const
{
	return CharacterName;
}

UTexture2D* UPA_CharacterDefinition::LoadIcon() const
{
	return CharacterIcon.LoadSynchronous();
}

TSubclassOf<ACCharacter> UPA_CharacterDefinition::LoadCharacterClass() const
{
	return CharacterClass.LoadSynchronous();
}

TSubclassOf<UAnimInstance> UPA_CharacterDefinition::LoadDisplayAnimBPClass() const
{
	return DisplayAnimBPClass.LoadSynchronous();
}

USkeletalMesh* UPA_CharacterDefinition::LoadDisplayMesh() const
{
	TSubclassOf<ACCharacter> CharacterClass = LoadCharacterClass();
	check(CharacterClass);
	
	ACharacter* Character = Cast<ACharacter>(CharacterClass.GetDefaultObject());
	if (!IsValid(Character))
	{
		return nullptr;
	}
	
	return Character->GetMesh()->GetSkeletalMeshAsset();
}
