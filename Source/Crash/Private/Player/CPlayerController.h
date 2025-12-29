// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

class UGameplayWidget;
class ACPlayerCharacter;
/**
 * 
 */
UCLASS()
class CRASH_API ACPlayerController : public APlayerController, public IGenericTeamAgentInterface
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
	
	void SpawnGameplayWidget();
	
	virtual void SetGenericTeamId(const FGenericTeamId& InTeamID) override;
	
	virtual FGenericTeamId GetGenericTeamId() const override;
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UGameplayWidget> GameplayWidgetClass;
	
private:
	
	UPROPERTY()
	TObjectPtr<ACPlayerCharacter> CPlayerCharacter;
	
	UPROPERTY()
	TObjectPtr<UGameplayWidget> GameplayWidget;
	
	UPROPERTY(Replicated)
	FGenericTeamId TeamId;
};
