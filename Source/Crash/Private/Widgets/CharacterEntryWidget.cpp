// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEntryWidget.h"

#include "Chatacter/PA_CharacterDefinition.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UCharacterEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	
	UPA_CharacterDefinition* InCharacterDefinition = Cast<UPA_CharacterDefinition>(ListItemObject);
	check(InCharacterDefinition);
	
	CharacterDefinition = InCharacterDefinition;
	
	CharacterIcon->GetDynamicMaterial()->SetTextureParameterValue(IconTextureMatParamName, InCharacterDefinition->LoadIcon());
	
	CharacterNameText->SetText(FText::FromString(InCharacterDefinition->GetCharacterDisplayName()));
}

const UPA_CharacterDefinition* UCharacterEntryWidget::GetCharacterDefinition() const
{
	return CharacterDefinition;
}

void UCharacterEntryWidget::SetSelected(bool bIsSelected)
{
	CharacterIcon->GetDynamicMaterial()->SetScalarParameterValue(SaturationMatParamName, !bIsSelected);
}
