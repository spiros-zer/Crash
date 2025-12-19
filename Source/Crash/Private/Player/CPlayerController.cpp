// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayerController.h"

#include "CPlayerCharacter.h"

void ACPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	CPlayerCharacter = Cast<ACPlayerCharacter>(InPawn);
	if (!IsValid(CPlayerCharacter)) return;
	CPlayerCharacter->ServerSideInit();
}

void ACPlayerController::AcknowledgePossession(APawn* InPawn)
{
	Super::AcknowledgePossession(InPawn);
	
	CPlayerCharacter = Cast<ACPlayerCharacter>(InPawn);
	if (!IsValid(CPlayerCharacter)) return;
	CPlayerCharacter->ClientSideInit();
}
