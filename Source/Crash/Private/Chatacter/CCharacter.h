// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "CCharacter.generated.h"

class UWidgetComponent;
class UCAttributeSet;
class UCAbilitySystemComponent;

UCLASS()
class CRASH_API ACCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	
	ACCharacter();
	
	virtual void BeginPlay() override;
	
	virtual void PossessedBy(AController* NewController) override;
	
	void ServerSideInit();
	
	void ClientSideInit();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
protected:
	
	virtual void OnDeath();
	
	virtual void OnRespawn();
	
	UPROPERTY(VisibleDefaultsOnly, Category = "AbilitySystem")
	TObjectPtr<UCAbilitySystemComponent> CAbilitySystemComponent;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "UI")
	TObjectPtr<UWidgetComponent> OverheadWidgetComponent;
	
	/** 
	 * The rate with which updates to the OverheadStatusGauge will be performed.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	float OverheadStatusGaugeVisibilityCheckUpdateGap = 1.f;
	
	/** 
	 * The square of the distance until which the OverheadStatusGauge will be visible.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	float OverheadStatusGaugeVisibilityRangeSquared = 10000000.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Death")
	TObjectPtr<UAnimMontage> DeathMontage;

private:
	
	void ConfigureOverheadStatusWidget();
	
	/** 
	 * Called to update the OverheadStatusGauge's visibility.
	 */
	void UpdateOverheadStatusGaugeVisibility();

	void BindGASChangeDelegates();
	
	void DeathTagUpdated(FGameplayTag GameplayTag, int NewCount);
	
	void StartDeathSequence();
	
	void Respawn();
	
	void PlayDeathAnimation();
	
	void SetStatusGaugeEnabled(bool bIsEnabled);
	
	UPROPERTY()
	TObjectPtr<UCAttributeSet> CAttributeSet;
	
	FTimerHandle OverheadStatusGaugeVisibilityTimerHandle;
};
