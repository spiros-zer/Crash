// Fill out your copyright notice in the Description page of Project Settings.


#include "TeamSelectionWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

void UTeamSelectionWidget::SetSlotID(uint8 InSlotID)
{
	SlotID = InSlotID;
}

void UTeamSelectionWidget::UpdateSlotInfo(const FString& PlayerNickname)
{
	InfoText->SetText(FText::FromString(PlayerNickname));
}

void UTeamSelectionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	SelectButton->OnClicked.AddUniqueDynamic(this, &ThisClass::SelectButtonClicked);
}

void UTeamSelectionWidget::SelectButtonClicked()
{
	OnSlotClicked.Broadcast(SlotID);
}
