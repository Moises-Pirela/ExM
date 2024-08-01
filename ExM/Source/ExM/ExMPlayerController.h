// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"
#include "ExMPlayerController.generated.h"

class UInputMappingContext;

UENUM(BlueprintType)
enum EInputDeviceType 
{
	DEVICE_UNKOWN,
	DEVICE_KBM,
	DEVICE_GAMEPAD
};

UCLASS()
class EXM_API AExMPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TEnumAsByte<EInputDeviceType> currentInputDevice;

	UPROPERTY(EditAnywhere, Category=Input)
	UInputMappingContext* defaultMappingContext;

	void OnAnyAction(FKey key);
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
};
