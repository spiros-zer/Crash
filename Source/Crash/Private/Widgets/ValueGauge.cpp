// Fill out your copyright notice in the Description page of Project Settings.


#include "ValueGauge.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UValueGauge::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	ProgressBar->SetFillColorAndOpacity(BarColor);
}

void UValueGauge::SetValue(float NewValue, float NewMaxValue)
{
	// Setting progressbar
	
	if (!NewMaxValue)
	{
		SetVisibility(ESlateVisibility::Hidden);
	
		return;
	}
	
	const float Percent = NewValue / NewMaxValue;
	
	ProgressBar->SetPercent(Percent);
	
	// Setting text
	
	FNumberFormattingOptions FormattingOptions;
	FormattingOptions.SetMaximumFractionalDigits(0);
	
	FTextFormat TextFormat = FTextFormat::FromString("{0}/{1}");
	FFormatNamedArguments Args;
	Args.Add("{0}", FText::AsNumber(NewValue, &FormattingOptions));
	Args.Add("{1}", FText::AsNumber(NewMaxValue, &FormattingOptions));
	
	ValueText->SetText(FText::Format(TextFormat, Args));
}
