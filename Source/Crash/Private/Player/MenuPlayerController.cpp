// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuPlayerController.h"

#include "Blueprint/UserWidget.h"

void AMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	SetInputMode(FInputModeUIOnly());
	
	SetShowMouseCursor(true);
	
	if (HasAuthority() && IsLocalPlayerController())
	{
		SpawnWidget();
	}
}

void AMenuPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	if (IsLocalPlayerController())
	{
		SpawnWidget();
	}
}

void AMenuPlayerController::SpawnWidget()
{
	check(MenuWidgetClass);
	
	MenuWidget = CreateWidget<UUserWidget>(this, MenuWidgetClass);
	check(MenuWidget);
	MenuWidget->AddToViewport();
}
