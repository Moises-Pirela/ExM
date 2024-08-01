// Copyright Epic Games, Inc. All Rights Reserved.


#include "ExMPlayerController.h"
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

}
