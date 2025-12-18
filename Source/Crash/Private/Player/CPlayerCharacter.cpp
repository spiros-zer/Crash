// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
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

void ACPlayerCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();
	
	APlayerController* OwningPlayerController = GetController<APlayerController>();
	if (!IsValid(OwningPlayerController)) return;
	
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = OwningPlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (!IsValid(InputSubsystem)) return;
	InputSubsystem->RemoveMappingContext(GameplayInputMappingContext);
	InputSubsystem->AddMappingContext(GameplayInputMappingContext, 0);
}

void ACPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!IsValid(EnhancedInputComponent)) return;
	EnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Triggered, this, &ThisClass::Jump);
}
