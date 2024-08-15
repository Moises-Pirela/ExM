// Copyright Epic Games, Inc. All Rights Reserved.

#include "ExMCharacter.h"
#include "ExMProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ExMPlayerController.h"
#include "InputActionValue.h"
#include "PersonaUtils.h"
#include "Engine/LocalPlayer.h"
#include "ExMCore/Components/ExmEquipmentComponent.h"
#include "ExMCore/Components/ExMHealthComponent.h"
#include "ExMCore/Components/ExMInteractionComponent.h"
#include "ExMCore/Components/ExMJumpComponent.h"
#include "ExMCore/Utils/DamageCalculators.h"
#include "ExMCore/Utils/Exmortalis.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AExMCharacter::AExMCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	//TODO: Add root components to apply leaning and sway correctly

	FPRoot = CreateDefaultSubobject<USceneComponent>("FP_Root");
	FPRoot->SetupAttachment(GetCapsuleComponent());

	CameraRoot = CreateDefaultSubobject<USpringArmComponent>("Camera_Root");
	CameraRoot->SetupAttachment(FPRoot);

	MeshRoot = CreateDefaultSubobject<USpringArmComponent>("Mesh_Root");
	MeshRoot->SetupAttachment(FPRoot);

	OffsetRoot = CreateDefaultSubobject<USceneComponent>("Offset_Root");
	OffsetRoot->SetupAttachment(MeshRoot);

	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(OffsetRoot);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	MeshLegs1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterLegsMesh1P"));
	MeshLegs1P->SetOnlyOwnerSee(true);
	MeshLegs1P->SetupAttachment(GetCapsuleComponent());
	MeshLegs1P->bCastDynamicShadow = false;
	MeshLegs1P->CastShadow = false;

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(CameraRoot);
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	jumpComponent = CreateDefaultSubobject<UExMJumpComponent>("JumpComponent");
	interactComponent = CreateDefaultSubobject<UExMInteractionComponent>("InteractionComponent");
	equipmentComponent = CreateDefaultSubobject<UExmEquipmentComponent>("EquipmentComponent");
}

void AExMCharacter::BeginPlay()
{
	Super::BeginPlay();

	currentStance = EStances::STANCE_STANDING;
	targetStanceCapsuleHeight = standCapsuleHeight;
	targetStanceEyeHeight = standEyeHeight;

	healthComponent = GetComponentByClass<UExMHealthComponent>();
}

void AExMCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// if (healthComponent->IsDead())
	// {
	// 	targetLeanRotAmount = -60;
	// 	targetLeanLocAmount = 0;
	// }

	FRotator targetRotation = FRotator(CameraRoot->GetRelativeRotation().Pitch, CameraRoot->GetRelativeRotation().Yaw,
	                                   targetLeanRotAmount);
	FRotator lerpedTarget = FMath::RInterpTo(CameraRoot->GetRelativeRotation(), targetRotation, DeltaSeconds, 10);
	CameraRoot->SetRelativeRotation(lerpedTarget);
	MeshRoot->SetRelativeRotation(lerpedTarget);

	FVector targetLocation = FVector(0, targetLeanLocAmount, CameraRoot->GetRelativeLocation().Z);
	FVector lerpedLocTarget = FMath::VInterpTo(CameraRoot->GetRelativeLocation(), targetLocation, DeltaSeconds, 10);

	CameraRoot->SetRelativeLocation(lerpedLocTarget);
	MeshRoot->SetRelativeLocation(lerpedLocTarget);

	//--------------CROUCH

	float alpha = targetStanceCapsuleHeight / GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
	float easedTarget = EaseInOutSine(alpha);
	float lerpedStanceTarget = FMath::Lerp(GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight(),
	                                       targetStanceCapsuleHeight, easedTarget * DeltaSeconds * stanceChangeSpeed);
	GetCapsuleComponent()->SetCapsuleHalfHeight(lerpedStanceTarget);
}

void AExMCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	float fallHeightDiff = startFallHeight - GetActorLocation().Z;

	if (fallHeightDiff > FALL_DAMAGE_THRESHOLD)
	{
		FDamageData damage;

		damage.baseDamage = fallHeightDiff;
		damage.damageType = EDamageTypes::DAMAGE_TYPE_FALL;

		healthComponent->TakeDamage(damage);
	}

	currentMovementMode = EExMMovementMode::Walk;

	ResetCoyoteTime();
	jumpComponent->ResetJump();
}

void AExMCharacter::Jump()
{
	Super::Jump();

	jumpComponent->currentJumpCount = FMath::Clamp(jumpComponent->currentJumpCount + 1, 0, jumpComponent->maxJumpCount);

	currentMovementMode = EExMMovementMode::Jump;
}

void AExMCharacter::StopJumping()
{
	Super::StopJumping();
}

void AExMCharacter::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PrevMovementMode, PreviousCustomMode);

	if (GetCharacterMovement()->MovementMode == MOVE_Falling)
	{
		startFallHeight = GetActorLocation().Z;

		GetWorldTimerManager().SetTimer(jumpComponent->coyoteTimerHandle, this, &AExMCharacter::ResetCoyoteTime,
		                                COYOTE_TIME, false);
	}
}

void AExMCharacter::ResetCoyoteTime()
{
	GetWorldTimerManager().ClearTimer(jumpComponent->coyoteTimerHandle);
	jumpComponent->coyoteTimerHandle.Invalidate();
}

void AExMCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AExMCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AExMCharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AExMCharacter::Move);
		EnhancedInputComponent->BindAction(PrimaryFireAction, ETriggerEvent::Triggered, this,
		                                   &AExMCharacter::PrimaryFire);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AExMCharacter::Look);

		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &AExMCharacter::Sprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AExMCharacter::CancelSprint);

		EnhancedInputComponent->BindAction(LeanAction, ETriggerEvent::Triggered, this, &AExMCharacter::Lean);
		EnhancedInputComponent->BindAction(LeanAction, ETriggerEvent::Completed, this, &AExMCharacter::StopLean);

		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &AExMCharacter::DoCrouch);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AExMCharacter::StartStand);
	}
}

void AExMCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AExMCharacter::CancelMove(const FInputActionValue& Value)
{
}

void AExMCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AExMCharacter::Sprint(const FInputActionValue& value)
{
	if (currentStance == EStances::STANCE_CROUCHING) return; //TODO: StartStand first?

	if (currentMovementMode != Walk || GetVelocity().Size() == 0) return;

	GetCharacterMovement()->MaxWalkSpeed = sprintSpeed;
	currentMovementMode = EExMMovementMode::Sprint;
}

void AExMCharacter::CancelSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
	currentMovementMode = EExMMovementMode::Walk;
}

void AExMCharacter::DoCrouch(const FInputActionValue& value)
{
	if (currentStance == EStances::STANCE_STANDING)
	{
		currentStance = EStances::STANCE_CROUCHING;
		GetCharacterMovement()->MaxWalkSpeed = crouchSpeed;
		targetStanceCapsuleHeight = crouchCapsuleHeight;
		GetWorld()->GetTimerManager().ClearTimer(checkCanStandTimerHandle);
	}
}

void AExMCharacter::StartStand()
{
	if (currentStance == EStances::STANCE_CROUCHING)
	{
		GetWorld()->GetTimerManager().ClearTimer(checkCanStandTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(checkCanStandTimerHandle,this, &AExMCharacter::TryStand, CAN_STAND_DURATION, true);
	}
}

void AExMCharacter::DoStand()
{
	GetWorld()->GetTimerManager().ClearTimer(checkCanStandTimerHandle);
	currentStance = EStances::STANCE_STANDING;
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
	targetStanceCapsuleHeight = standCapsuleHeight;
}

void AExMCharacter::TryStand()
{
	float _stanceHeightDiff = crouchCapsuleHeight - standCapsuleHeight;
	float _z = GetActorLocation().Z + crouchCapsuleHeight;
	float _lerpedHeight = (FMath::Lerp(0, _stanceHeightDiff,  1 - GetWorld()->GetDeltaSeconds()) * 1.1) + _z;
	FVector _startTraceLocation = FVector(GetActorLocation().X, GetActorLocation().Y, _z);
	FVector _endTraceLocation = FVector(GetActorLocation().X, GetActorLocation().Y, _lerpedHeight);

	FHitResult hit;
	FCollisionQueryParams params(NAME_None, false, this);
	FCollisionShape sphereShape = FCollisionShape::MakeSphere(GetCapsuleComponent()->GetUnscaledCapsuleRadius());

	if (GetWorld()->SweepSingleByChannel(hit, _startTraceLocation, _endTraceLocation, FQuat::Identity,ECC_Visibility, sphereShape, params))
	{
		return;
	}

	DoStand();
}

void AExMCharacter::Lean(const FInputActionValue& value)
{
	float leanDirection = value.Get<float>();

	leanDirection = FMath::Clamp(leanDirection, -1, 1);

	float rollAmount = leanDirection * maxLeanRotationAmount;
	float yMoveAmount = leanDirection * maxLeanLocationAmount;

	FRotator currentRotation = GetFirstPersonCameraComponent()->GetRelativeRotation();
	FVector currentLocation = GetFirstPersonCameraComponent()->GetRelativeLocation();

	targetLeanRotAmount = FMath::Clamp(currentRotation.Roll + rollAmount, -maxLeanRotationAmount,
	                                   maxLeanRotationAmount);
	targetLeanLocAmount = FMath::Clamp(currentLocation.Y + yMoveAmount, -maxLeanLocationAmount, maxLeanLocationAmount);
}

void AExMCharacter::StopLean(const FInputActionValue& value)
{
	targetLeanRotAmount = 0;
	targetLeanLocAmount = 0;
}

void AExMCharacter::PrimaryFire()
{
	if (interactComponent->grabbedComponent)
	{
		UPrimitiveComponent* grabbedComp = interactComponent->grabbedComponent;

		interactComponent->physicsHandleComponent->ReleaseComponent();
		grabbedComp->SetPhysicsLinearVelocity(FVector::Zero());

		FVector throwDirection = GetActorForwardVector();
		interactComponent->grabbedComponent = nullptr;
		interactComponent->currentInteractionType = INTERACTION_NONE;

		float throwStrength = 1000.0f; //TODO: Calculate throw strength
		grabbedComp->AddImpulse(throwDirection * throwStrength, NAME_None, true);
		return;
	}

	//TODO: Shoot

	equipmentComponent->FireWeapon();
}

void AExMCharacter::SecondaryFire()
{
	equipmentComponent->SecondaryFire();
}
