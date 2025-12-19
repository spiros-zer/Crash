// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TeamSelectionWidget.generated.h"

class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class CRASH_API UTeamSelectionWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	void SetSlotID(uint8 InSlotID);
	
	void UpdateSlotInfo(const FString& PlayerNickname);
	
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnSlotClickedSignature, uint8 /** SlotID*/);
	FOnSlotClickedSignature OnSlotClicked;
	
protected:
	
	virtual void NativeOnInitialized() override;
	
	UFUNCTION()
	void SelectButtonClicked();
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> SelectButton;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> InfoText;
	
	uint8 SlotID = -1;
};
