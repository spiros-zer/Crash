// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterDisplay.generated.h"

class UPA_CharacterDefinition;
class UCameraComponent;
/** 
 * Displays the character on the character selection screen.
 */
UCLASS()
class CRASH_API ACharacterDisplay : public AActor
{
	GENERATED_BODY()

public:
	
	ACharacterDisplay();

	void ConfigureWithCharacterDefinition(const UPA_CharacterDefinition* CharacterDefinition);
	
private:
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Character Display")
	TObjectPtr<USkeletalMeshComponent> MeshComponent;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Character Display")
	TObjectPtr<UCameraComponent> ViewCameraComponent;
};
