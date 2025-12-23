// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Player/PlayerInfoTypes.h"
#include "LobbyWidget.generated.h"

class ACPlayerState;
class UTileView;
class ACGameState;
class ALobbyPlayerController;
class UTeamSelectionWidget;
class UUniformGridPanel;
class UButton;
class UWidgetSwitcher;

/**
 * Base display to show all the widgets related to the lobby.
 */
UCLASS()
class CRASH_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeOnInitialized() override;
	
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> StartHeroSelectionButton;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTileView> CharacterSelectionTileView;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> TeamSelectionSlotGridPanel;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidget> TeamSelectionRoot;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidget> HeroSelectionRoot;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> MainSwitcher;
	
private:
	
	void ClearAndPopulateTeamSelectionSlots();
	
	void SlotSelected(uint8 NewSlotID);

	void ConfigureGameState();
	
	void UpdatePlayerSelectionDisplay(const TArray<FPlayerSelection>& PlayerSelections);
	
	/** 
	 * Called when the StartHeroSelectionButton is clicked. Swaps every player to the hero selection screen.
	 */
	UFUNCTION()
	void StartHeroSelectionButtonClicked();
	
	void SwitchToHeroSelection();
	
	void CharacterDefinitionLoaded();
	
	void CharacterSelected(UObject* SelectedUObject);
	
	UPROPERTY()
	TObjectPtr<ACPlayerState> CPlayerState;
	
	UPROPERTY(EditDefaultsOnly, Category= "TeamSelection")
	TSubclassOf<UTeamSelectionWidget> TeamSelectionWidgetClass;
	
	UPROPERTY()
	TArray<TObjectPtr<UTeamSelectionWidget>> TeamSelectionSlots;
	
	UPROPERTY()
	TObjectPtr<ALobbyPlayerController> LobbyPlayerController;
	
	UPROPERTY()
	TObjectPtr<ACGameState> CGameState;
	
	FTimerHandle ConfigureGameStateTimerHandle;
};
