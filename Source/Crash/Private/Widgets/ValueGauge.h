// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ValueGauge.generated.h"

class UTextBlock;
class UProgressBar;
/**
 * 
 */
UCLASS()
class CRASH_API UValueGauge : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	virtual void NativePreConstruct() override;
	
	void SetValue(float NewValue, float NewMaxValue);
	
private:
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> ProgressBar;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ValueText;
	
	UPROPERTY(EditAnywhere, Category = "Visual")
	FLinearColor BarColor;
};
