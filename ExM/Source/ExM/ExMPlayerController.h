// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"
#include "ExMPlayerController.generated.h"

class UEntitySubsystem;
class UInputMappingContext;

UENUM(BlueprintType)
enum EInputDeviceType {
	DEVICE_UNKOWN,
	DEVICE_KBM,
	DEVICE_GAMEPAD
};

UCLASS()
class EXM_API AExMPlayerController : public APlayerController {
	GENERATED_BODY()

public:
	UEntitySubsystem* entitySubsytem;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TEnumAsByte<EInputDeviceType> currentInputDevice;

	UPROPERTY(EditAnywhere, Category=Input)
	UInputMappingContext* defaultMappingContext;

	// INPUT
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SprintAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* CrouchAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* PrimaryFireAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SecondaryFireAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* LeanAction;
	//

	void OnAnyAction(FKey key);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void OnJump();
	void OnCancelJump();
	void OnMove(const FInputActionValue& Value);
	void OnLook(const FInputActionValue& Value);
	void OnBeginSprint(const FInputActionValue& value);
	void OnCancelSprint(const FInputActionValue& value);
	void OnPrimaryFire();
	void OnLean();
	void OnCancelLean();
	void OnCrouch();
	void OnCancelCrouch();
};
