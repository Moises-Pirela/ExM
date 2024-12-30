// Copyright Epic Games, Inc. All Rights Reserved.


#include "ExMPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

void AExMPlayerController::OnAnyAction(FKey key)
{
	if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (key.IsGamepadKey())
		{
			currentInputDevice = DEVICE_GAMEPAD;
		}
		if (!key.IsGamepadKey() || key.IsMouseButton())
		{
			currentInputDevice = DEVICE_KBM;
		}
	}
}

void AExMPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(defaultMappingContext, 0);
	}
}

void AExMPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindAction("AnyKey", IE_Pressed, this, &AExMPlayerController::OnAnyAction);

	if(UEnhancedInputComponent* _enhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		_enhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AExMPlayerController::OnJump);
		_enhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AExMPlayerController::OnCancelJump);

		_enhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AExMPlayerController::OnMove);

		_enhancedInputComponent->BindAction(PrimaryFireAction, ETriggerEvent::Started, this, &AExMPlayerController::OnPrimaryFire);

		_enhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AExMPlayerController::OnLook);

		_enhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &AExMPlayerController::OnBeginSprint);
		_enhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AExMPlayerController::OnCancelSprint);

		_enhancedInputComponent->BindAction(LeanAction, ETriggerEvent::Triggered, this, &AExMPlayerController::OnLean);
		_enhancedInputComponent->BindAction(LeanAction, ETriggerEvent::Completed, this, &AExMPlayerController::OnCancelLean);

		_enhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &AExMPlayerController::OnCrouch);
		_enhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AExMPlayerController::OnCancelCrouch);
	}
}

void AExMPlayerController::OnJump()
{
}

void AExMPlayerController::OnCancelJump()
{
}

void AExMPlayerController::OnMove(const FInputActionValue& Value)
{
}

void AExMPlayerController::OnLook(const FInputActionValue& Value)
{
}

void AExMPlayerController::OnBeginSprint(const FInputActionValue& value)
{
	
}

void AExMPlayerController::OnCancelSprint(const FInputActionValue& value)
{
}

void AExMPlayerController::OnPrimaryFire()
{
}

void AExMPlayerController::OnLean()
{
}

void AExMPlayerController::OnCancelLean()
{
}

void AExMPlayerController::OnCrouch()
{
}

void AExMPlayerController::OnCancelCrouch()
{
}
