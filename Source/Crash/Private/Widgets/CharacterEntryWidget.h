// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "CharacterEntryWidget.generated.h"

class UPA_CharacterDefinition;
class UTextBlock;
class UImage;

/**
 * 
 */
UCLASS()
class CRASH_API UCharacterEntryWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:
	
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	
	FORCEINLINE const UPA_CharacterDefinition* GetCharacterDefinition() const;
	
	void SetSelected(bool bIsSelected);
	
protected:
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> CharacterIcon;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CharacterNameText;
	
	UPROPERTY(EditDefaultsOnly, Category = "Character")
	FName IconTextureMatParamName = FName("Icon"); 
	
	UPROPERTY(EditDefaultsOnly, Category = "Character")
	FName SaturationMatParamName = FName("Saturation"); 
	
	UPROPERTY()
	TObjectPtr<UPA_CharacterDefinition> CharacterDefinition;
};
