// Fill out your copyright notice in the Description page of Project Settings.


#include "CGameplayAbility.h"

#include "Kismet/KismetSystemLibrary.h"

TObjectPtr<UAnimInstance> UCGameplayAbility::GetOwnerAnimInstance() const
{
	const USkeletalMeshComponent* OwnerSkeletalMeshComponent = GetOwningComponentFromActorInfo();
	if (!IsValid(OwnerSkeletalMeshComponent))
	{
		return nullptr;
	}
	
	return OwnerSkeletalMeshComponent->GetAnimInstance();
}

TArray<FHitResult> UCGameplayAbility::GetHitResultFromSweepLocationTargetData(const FGameplayAbilityTargetDataHandle& TargetDataHandle, float SphereSweepRadius, ETeamAttitude::Type TargetTeam, bool bDrawDebug, bool bIgnoreSelf) const
{
	TArray<FHitResult> OutResults;
	
	TSet <AActor*> HitActors;
	
	IGenericTeamAgentInterface* OwnerTeamInterface = Cast<IGenericTeamAgentInterface>(GetAvatarActorFromActorInfo());
	
	for (const TSharedPtr<FGameplayAbilityTargetData> TargetData : TargetDataHandle.Data)
	{
		const FVector StartLocation = TargetData->GetOrigin().GetTranslation();

		const FVector EndLocation = TargetData->GetEndPoint();
		
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectType;
		ObjectType.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
		
		TArray<AActor*> ActorsToIgnore;
		
		if (bIgnoreSelf)
		{
			ActorsToIgnore.Add(GetAvatarActorFromActorInfo());
		}
		
		TArray<FHitResult> Results;
		
		EDrawDebugTrace::Type DrawDebugTrace = bDrawDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None;		
		
		UKismetSystemLibrary::SphereTraceMultiForObjects(this, StartLocation, EndLocation, SphereSweepRadius, ObjectType, false, ActorsToIgnore, DrawDebugTrace, Results, false);
		
		for (const FHitResult& Result : Results)
		{
			// Avoid duplicate actors hit by the swipes.
			
			if (HitActors.Contains(Result.GetActor())) continue;
			
			// Don't deal damage on teammates.
			
			if (OwnerTeamInterface)
			{
				ETeamAttitude::Type OtherActorTeamAttitude = OwnerTeamInterface->GetTeamAttitudeTowards(*Result.GetActor());
				
				if (OtherActorTeamAttitude != TargetTeam) continue;
			}
			
			HitActors.Add(Result.GetActor());
			
			OutResults.Add(Result);
		}
	}
	
	return OutResults;
}
