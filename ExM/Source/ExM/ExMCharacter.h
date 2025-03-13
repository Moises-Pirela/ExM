// Copyright Epic Games, Inc. All Rights Reserved.

	#pragma once

	#include "CoreMinimal.h"
	#include "InputActionValue.h"
#include "Components/TimelineComponent.h"
	#include "GameFramework/Character.h"
	#include "Logging/LogMacros.h"
	#include "ExMCharacter.generated.h"

struct FTimeline;
class UExmInventoryComponent;
class UExmStatsComponent;
class USpringArmComponent;
class UExmEquipmentComponent;
class UExMInteractionComponent;
class UExMHealthComponent;
class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AExMCharacter : public ACharacter {
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

	// INPUT
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess = "true"))
	float maxLeanRotationAmount = 5;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess = "true"))
	float maxLeanLocationAmount = 20;

	float startFallHeight;
	float targetLeanRotAmount;
	float targetLeanLocAmount;

	FTimerHandle checkCanStandTimerHandle;

public:
	AExMCharacter();

	FTimerHandle sprintChargeTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess = "true"))
	float walkSpeed = 375;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess = "true"))
	float sprintSpeed = 450;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess = "true"))
	float crouchSpeed = 300;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Components")
	UExMInteractionComponent* interactComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Components")
	UExmEquipmentComponent* equipmentComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Components")
	UExMHealthComponent* healthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Components")
	UExmStatsComponent* statsComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Crouch")
	float crouchAlpha;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Crouch")
	float crouchAnimAlpha;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Sway")
	FVector pitchOffsetPos;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Sway")
	FVector camRotOffset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Sway")
	FRotator camRotCurrent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Sway")
	FRotator camRotRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Sway")
	FRotator inAirTilt;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Sway")
	FVector inAirOffSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Sprint")
	float sprintCharge;

	UPROPERTY(EditAnywhere, Category = "Vaulting")
	UCurveFloat* VaultCurve;
	FTimeline    vaultTimeline;
	FVector      vaultStartLocation;
	FVector      vaultEndLocation;

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;
	virtual void Jump() override;

protected:
	virtual void Tick(float DeltaSeconds) override;
	virtual void Landed(const FHitResult& Hit) override;
	virtual void StopJumping() override;
	void		 TryJump();
	void         Move(const FInputActionValue& Value);
	void         Look(const FInputActionValue& Value);
	void         Sprint(const FInputActionValue& value);
	void         CancelSprint();
	void         StartSlide();
	UFUNCTION(BlueprintImplementableEvent)
	void SlideTL();
	UFUNCTION(BlueprintCallable)
	void CheckStopSprint(float inAxis);
	void Lean(const FInputActionValue& value);
	void StopLean(const FInputActionValue& value);
	void PrimaryFire();
	void SecondaryFire();

	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode) override;

	UFUNCTION(BlueprintCallable)
	void DoCrouch();

	UFUNCTION()
	void OnVaultProgress(float Value);
	UFUNCTION()
	void OnVaultFinished();
	void StartVault(FVector TargetLocation);
	bool TryVault();

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

public:
	USkeletalMeshComponent* GetMesh1P() const
	{
		return Mesh1P;
	}

	UCameraComponent* GetFirstPersonCameraComponent() const
	{
		return FirstPersonCameraComponent;
	}

	UFUNCTION(BlueprintCallable)
	FVector GetVelocityVars(FVector outLagPos);

	UFUNCTION(BlueprintCallable)
	void GetLookInputVars(FRotator camPosPrev);
};
