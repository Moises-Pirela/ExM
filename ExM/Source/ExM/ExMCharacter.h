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
	enum EStances {
		STANCE_STANDING,
		STANCE_CROUCHING
	};

	constexpr float CAN_STAND_DURATION = 0.01667f;

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
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess = "true"))
		float crouchCapsuleHeight = 60;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess = "true"))
		float standCapsuleHeight = 90;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess = "true"))
		float stanceChangeSpeed = 10;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess = "true"))
		float crouchEyeHeight = 20;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess = "true"))
		float standEyeHeight = 50;

		float startFallHeight;
		float targetLeanRotAmount;
		float targetLeanLocAmount;
		float targetStanceCapsuleHeight;
		float targetStanceEyeHeight;

		EStances     currentStance;
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
		UExMJumpComponent* jumpComponent;

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
		FTimeline vaultTimeline;
		FVector vaultStartLocation;
		FVector vaultEndLocation;

	protected:
		virtual void BeginPlay() override;

	public:
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* LookAction;

	protected:
		virtual void Tick(float DeltaSeconds) override;
		virtual void Landed(const FHitResult& Hit) override;
		virtual void Jump() override;
		virtual void StopJumping() override;
		void         Move(const FInputActionValue& Value);
		void         Look(const FInputActionValue& Value);
		void         Sprint(const FInputActionValue& value);
		void         CancelSprint();
		void		 StartSlide();
		UFUNCTION(BlueprintImplementableEvent)
		void		 SlideTL();
		UFUNCTION(BlueprintCallable)
		void CheckStopSprint(float inAxis);
		void IncreaseSprintCharge();
		UFUNCTION(BlueprintCallable)
		void DoCrouch();
		void StartStand();
		void DoStand();
		void Lean(const FInputActionValue& value);
		void StopLean(const FInputActionValue& value);
		void PrimaryFire();
		void SecondaryFire();
		void TryStand();

		virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode) override;
		void         ResetCoyoteTime();

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
