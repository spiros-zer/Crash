// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidget.h"

#include "TeamSelectionWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Network/CNetStatics.h"

void ULobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	ClearAndPopulateTeamSelectionSlots();
}

void ULobbyWidget::ClearAndPopulateTeamSelectionSlots()
{
	TeamSelectionSlotGridPanel->ClearChildren();
	
	for (int Index = 0; Index < UCNetStatics::GetPlayerCountPerTeam() * 2; ++Index)
	{
		UTeamSelectionWidget* NewSelectionSlot = CreateWidget<UTeamSelectionWidget>(this, TeamSelectionWidgetClass);
		check(NewSelectionSlot);
		NewSelectionSlot->SetSlotID(Index);
		NewSelectionSlot->OnSlotClicked.AddUObject(this, &ThisClass::SlotSelected);
		
		TeamSelectionSlots.Add(NewSelectionSlot);
		
		const int Row = Index % UCNetStatics::GetPlayerCountPerTeam();
		const int Column = Index < UCNetStatics::GetPlayerCountPerTeam() ? 0 : 1;
		
		UUniformGridSlot* NewGridSlot = TeamSelectionSlotGridPanel->AddChildToUniformGrid(NewSelectionSlot);
		check(NewGridSlot);
		NewGridSlot->SetColumn(Column);
		NewGridSlot->SetRow(Row);
	}
}

void ULobbyWidget::SlotSelected(uint8 NewSlotID)
{
	
}
