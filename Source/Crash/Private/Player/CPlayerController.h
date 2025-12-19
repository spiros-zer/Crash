// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

class ACPlayerCharacter;
/**
 * 
 */
UCLASS()
class CRASH_API ACPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	
	/** 
	 * Called only on server.
	 */
	virtual void OnPossess(APawn* InPawn) override;
	
	/** 
	 * Called only on client.
	 */
	virtual void AcknowledgePossession(APawn* InPawn) override;
	
private:
	
	UPROPERTY()
	TObjectPtr<ACPlayerCharacter> CPlayerCharacter;
};
