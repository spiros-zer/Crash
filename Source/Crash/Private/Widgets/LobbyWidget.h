// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidget.generated.h"

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
	
	virtual void NativeConstruct() override;
	
	void ClearAndPopulateTeamSelectionSlots();
	
	void SlotSelected(uint8 NewSlotID);
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> MainSwitcher;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidget> TeamSelectionRoot;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> StartHeroSelectionButton;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> TeamSelectionSlotGridPanel;
	
	UPROPERTY(EditDefaultsOnly, Category= "TeamSelection")
	TSubclassOf<UTeamSelectionWidget> TeamSelectionWidgetClass;
	
	UPROPERTY()
	TArray<TObjectPtr<UTeamSelectionWidget>> TeamSelectionSlots;
};
