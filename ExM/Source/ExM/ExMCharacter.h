// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "ExMCharacter.generated.h"

class UMovieSceneColorPropertySystem;
class USpringArmComponent;
class UExmEquipmentComponent;
class UExMInteractionComponent;
class UExMJumpComponent;
class UExMHealthComponent;
class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UENUM(BlueprintType)
enum EStances
{
	Standing,
	Crouching
};

UENUM(BlueprintType)
enum EExMMovementMode
{
	Walk,
	Sprint,
	Vault,
	Jump,
};

UCLASS(config=Game)
class AExMCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	USceneComponent* FPRoot;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	USceneComponent* OffsetRoot;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraRoot;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* MeshRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh1P;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* MeshLegs1P;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess = "true"))
	float walkSpeed = 375;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess = "true"))
	float sprintSpeed = 450;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess = "true"))
	float crouchSpeed = 300;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess = "true"))
	float maxLeanRotationAmount = 5;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess = "true"))
	float maxLeanLocationAmount = 20;

	float startFallHeight;
	float targetLeanRotAmount;
	float targetLeanLocAmount;

	EStances currentStance;
	TEnumAsByte<EExMMovementMode> prevMovementMode;

public:
	AExMCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TEnumAsByte<EExMMovementMode> currentMovementMode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Components")
	UExMJumpComponent* jumpComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Components")
	UExMInteractionComponent* interactComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Components")
	UExmEquipmentComponent* equipmentComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Components")
	UExMHealthComponent* healthComponent;

protected:
	virtual void BeginPlay() override;

public:
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

protected:
	virtual void Tick(float DeltaSeconds) override;
	virtual void Landed(const FHitResult& Hit) override;
	virtual void Jump() override;
	virtual void StopJumping() override;
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Sprint(const FInputActionValue& value);
	void CancelSprint();
	void Crouch(const FInputActionValue& value);
	void Lean(const FInputActionValue& value);
	void StopLean(const FInputActionValue& value);
	void PrimaryFire();
	void SecondaryFire();
	bool CanStand();


	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode) override;
	void ResetCoyoteTime();

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

public:
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
};
