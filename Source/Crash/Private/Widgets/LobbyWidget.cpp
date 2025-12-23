// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidget.h"

#include "CharacterDisplay.h"
#include "CharacterEntryWidget.h"
#include "TeamSelectionWidget.h"
#include "Chatacter/PA_CharacterDefinition.h"
#include "Components/Button.h"
#include "Components/TileView.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Components/WidgetSwitcher.h"
#include "Framework/CAssetManager.h"
#include "Framework/CGameState.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Network/CNetStatics.h"
#include "Player/CPlayerState.h"
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
	
	CharacterSelectionTileView->OnItemSelectionChanged().AddUObject(this, &ThisClass::CharacterSelected);
	
	SpawnCharacterDisplay();
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
	
	// Clear entry
	
	for (UUserWidget* CharacterEntryAsWidget : CharacterSelectionTileView->GetDisplayedEntryWidgets())
	{
		UCharacterEntryWidget* CharacterEntryWidget = Cast<UCharacterEntryWidget>(CharacterEntryAsWidget);
		if (!IsValid(CharacterEntryWidget)) continue;
		
		CharacterEntryWidget->SetSelected(false);
	}
	
	for (const FPlayerSelection& PlayerSelection : PlayerSelections)
	{
		if (!PlayerSelection.IsPlayerSelectionValid()) continue;
		
		TeamSelectionSlots[PlayerSelection.GetSlotID()]->UpdateSlotInfo(PlayerSelection.GetPlayerNickName());
		
		// Clear entry
		
		UCharacterEntryWidget* SelectedEntry = CharacterSelectionTileView->GetEntryWidgetFromItem<UCharacterEntryWidget>(PlayerSelection.GetCharacterDefinition());
		if (!IsValid(SelectedEntry)) continue;
		SelectedEntry->SetSelected(true);
		
		if (PlayerSelection.IsForPlayer(GetOwningPlayerState()))
		{
			UpdateCharacterDisplay(PlayerSelection);
		}
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

void ULobbyWidget::CharacterSelected(UObject* SelectedUObject)
{
	if (!IsValid(CPlayerState))
	{
		CPlayerState = GetOwningPlayerState<ACPlayerState>();
	}
	
	if (!IsValid(CPlayerState)) return;
	
	const UPA_CharacterDefinition* CharacterDefinition = Cast<UPA_CharacterDefinition>(SelectedUObject);
	check(CharacterDefinition);
	
	CPlayerState->Server_SetSelectedCharacterDefinition(CharacterDefinition);
}

void ULobbyWidget::SpawnCharacterDisplay()
{
	check(IsValid(CharacterDisplayClass));
	
	if (CharacterDisplay) return;
	
	UWorld* World = GetWorld();
	if (!IsValid(World)) return;
	
	// Configuring spawn location
	
	FTransform CharacterDisplayTransform = FTransform::Identity;

	if (const AActor* PlayerStart = UGameplayStatics::GetActorOfClass(World, APlayerStart::StaticClass()))
	{
		CharacterDisplayTransform = PlayerStart->GetActorTransform();
	}
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	CharacterDisplay = World->SpawnActor<ACharacterDisplay>(CharacterDisplayClass, SpawnParams);
	
	GetOwningPlayer()->SetViewTarget(CharacterDisplay);
}

void ULobbyWidget::UpdateCharacterDisplay(const FPlayerSelection& PlayerSelection)
{
	if (!PlayerSelection.GetCharacterDefinition()) return;
	
	CharacterDisplay->ConfigureWithCharacterDefinition(PlayerSelection.GetCharacterDefinition());
}
