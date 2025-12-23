// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterDisplay.h"

#include "Camera/CameraComponent.h"
#include "Chatacter/PA_CharacterDefinition.h"


ACharacterDisplay::ACharacterDisplay()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("RootComponent"));
	
	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("MeshComponent");
	MeshComponent->SetupAttachment(RootComponent);
	
	ViewCameraComponent = CreateDefaultSubobject<UCameraComponent>("ViewCameraComponent");
	ViewCameraComponent->SetupAttachment(MeshComponent);
}

void ACharacterDisplay::ConfigureWithCharacterDefinition(const UPA_CharacterDefinition* CharacterDefinition)
{
	check(CharacterDefinition);
	
	// Load meshes on-demand.
	
	MeshComponent->SetSkeletalMesh(CharacterDefinition->LoadDisplayMesh());
	MeshComponent->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	MeshComponent->SetAnimInstanceClass(CharacterDefinition->LoadDisplayAnimBPClass());
}
