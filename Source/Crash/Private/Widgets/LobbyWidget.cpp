// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidget.h"

#include "TeamSelectionWidget.h"
#include "Chatacter/PA_CharacterDefinition.h"
#include "Components/Button.h"
#include "Components/TileView.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Components/WidgetSwitcher.h"
#include "Framework/CAssetManager.h"
#include "Framework/CGameState.h"
#include "Network/CNetStatics.h"
#include "Player/LobbyPlayerController.h"

void ULobbyWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	LobbyPlayerController = GetOwningPlayer<ALobbyPlayerController>();
	check(LobbyPlayerController);
	LobbyPlayerController->SwitchToHeroSelection.BindUObject(this, &ThisClass::SwitchToHeroSelection);
	
	ConfigureGameState();
	
	StartHeroSelectionButton->SetIsEnabled(false);
	StartHeroSelectionButton->OnClicked.AddUniqueDynamic(this, &ThisClass::StartHeroSelectionButtonClicked);
	
	UCAssetManager::Get().LoadCharacterDefinitions(FStreamableDelegate::CreateUObject(this, &ThisClass::CharacterDefinitionLoaded));
}

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
	LobbyPlayerController->Server_RequestSlotSelectionChange(NewSlotID);
}

void ULobbyWidget::ConfigureGameState()
{
	UWorld* World = GetWorld();
	if (!IsValid(World)) return;
	
	CGameState = World->GetGameState<ACGameState>();
	if (!IsValid(CGameState))
	{
		World->GetTimerManager().SetTimer(ConfigureGameStateTimerHandle, this, &ThisClass::ConfigureGameState, 1.f);
	}
	else
	{
		CGameState->OnPlayerSelectionUpdated.AddUObject(this, &ThisClass::UpdatePlayerSelectionDisplay);
		UpdatePlayerSelectionDisplay(CGameState->GetPlayerSelectionArray());
	}
}

void ULobbyWidget::UpdatePlayerSelectionDisplay(const TArray<FPlayerSelection>& PlayerSelections)
{
	for (UTeamSelectionWidget* SelectionSlot : TeamSelectionSlots)
	{
		SelectionSlot->UpdateSlotInfo("Empty");
	}
	
	for (const FPlayerSelection& PlayerSelection : PlayerSelections)
	{
		if (!PlayerSelection.IsPlayerSelectionValid()) continue;
		
		TeamSelectionSlots[PlayerSelection.GetSlotID()]->UpdateSlotInfo(PlayerSelection.GetPlayerNickName());
	}
	
	// Check whether we can now proceed to hero selection

	if (!IsValid(CGameState)) return;
	
	StartHeroSelectionButton->SetIsEnabled(CGameState->CanStartHeroSelection());
}

void ULobbyWidget::StartHeroSelectionButtonClicked()
{
	if (!IsValid(LobbyPlayerController)) return;
	
	LobbyPlayerController->Server_StartHeroSelection();
}

void ULobbyWidget::SwitchToHeroSelection()
{
	MainSwitcher->SetActiveWidget(HeroSelectionRoot);
}

void ULobbyWidget::CharacterDefinitionLoaded()
{
	TArray<UPA_CharacterDefinition*> LoadedCharacterDefinitions;
	if (!UCAssetManager::Get().GetLoadedCharacterDefinitions(LoadedCharacterDefinitions)) return;
	
	CharacterSelectionTileView->SetListItems(LoadedCharacterDefinitions);
}
