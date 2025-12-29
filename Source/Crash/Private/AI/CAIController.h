// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CAIController.generated.h"

class UAISenseConfig_Sight;

UCLASS()
class CRASH_API ACAIController : public AAIController
{
	GENERATED_BODY()

public:

	ACAIController();
	
	virtual void OnPossess(APawn* InPawn) override;
	
protected:
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Perception")
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Perception")
	TObjectPtr<UAISenseConfig_Sight> SightConfig;
	
	UPROPERTY(EditDefaultsOnly, Category = "Perception")
	float SightRadius = 1000.f;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Perception")
	float LoseSightRadius = 1200.f;
	
	/** 
	 * Time until the AI forgets you when leaving its sight.
	 */
	UPROPERTY(VisibleDefaultsOnly, Category = "Perception")
	float SightMaxAge = 5.f;
};
