// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
ACPlayerCharacter::ACPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(RootComponent);
	
	ViewCamera = CreateDefaultSubobject<UCameraComponent>("ViewCamera");
	ViewCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
}
