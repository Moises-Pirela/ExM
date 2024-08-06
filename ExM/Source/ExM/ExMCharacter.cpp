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
#include "Engine/LocalPlayer.h"
#include "ExMCore/Components/ExmEquipmentComponent.h"
#include "ExMCore/Components/ExMHealthComponent.h"
#include "ExMCore/Components/ExMInteractionComponent.h"
#include "ExMCore/Components/ExMJumpComponent.h"
#include "ExMCore/Utils/DamageCalculators.h"
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
	
	jumpComponent      = CreateDefaultSubobject<UExMJumpComponent>("JumpComponent");
	interactComponent  = CreateDefaultSubobject<UExMInteractionComponent>("InteractionComponent");
	equipmentComponent = CreateDefaultSubobject<UExmEquipmentComponent>("EquipmentComponent");
}

void AExMCharacter::BeginPlay()
{
	Super::BeginPlay();

	currentStance = EStances::Standing;

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
	
	FRotator targetRotation = FRotator(CameraRoot->GetRelativeRotation().Pitch, CameraRoot->GetRelativeRotation().Yaw, targetLeanRotAmount);
	FRotator lerpedTarget = FMath::RInterpTo(CameraRoot->GetRelativeRotation(), targetRotation, DeltaSeconds, 10);
	CameraRoot->SetRelativeRotation(lerpedTarget);
	MeshRoot->SetRelativeRotation(lerpedTarget);

	FVector targetLocation = FVector(0, targetLeanLocAmount, CameraRoot->GetRelativeLocation().Z);
	FVector lerpedLocTarget = FMath::VInterpTo(CameraRoot->GetRelativeLocation(), targetLocation, DeltaSeconds, 10);

	CameraRoot->SetRelativeLocation(lerpedLocTarget);
	MeshRoot->SetRelativeLocation(lerpedLocTarget);
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

	ResetCoyoteTime();
	jumpComponent->ResetJump();
	currentMovementMode = EExMMovementMode::Walk;
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
		EnhancedInputComponent->BindAction(PrimaryFireAction, ETriggerEvent::Triggered, this, &AExMCharacter::PrimaryFire);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AExMCharacter::Look);

		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &AExMCharacter::Sprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AExMCharacter::CancelSprint);

		EnhancedInputComponent->BindAction(LeanAction, ETriggerEvent::Triggered, this, &AExMCharacter::Lean);
		EnhancedInputComponent->BindAction(LeanAction, ETriggerEvent::Completed, this, &AExMCharacter::StopLean);
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
	if (currentStance == EStances::Crouching) return; //TODO: Stand first?

	if (currentMovementMode != Walk || GetVelocity().Size() == 0) return;

	GetCharacterMovement()->MaxWalkSpeed = sprintSpeed;
	currentMovementMode = EExMMovementMode::Sprint;
}

void AExMCharacter::CancelSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
	currentMovementMode = EExMMovementMode::Walk;
}

void AExMCharacter::Crouch(const FInputActionValue& value)
{
	if (currentStance == EStances::Standing)
	{
		currentStance = EStances::Crouching;
		Super::Crouch();
	}
	else if (currentStance == EStances::Crouching && CanStand())
	{
		currentStance = EStances::Standing;
		Super::UnCrouch();
	}
}

void AExMCharacter::Lean(const FInputActionValue& value)
{
	float leanDirection = value.Get<float>();

	leanDirection = FMath::Clamp(leanDirection, -1, 1);

	float rollAmount = leanDirection * maxLeanRotationAmount;
	float yMoveAmount = leanDirection * maxLeanLocationAmount;

	FRotator currentRotation = GetFirstPersonCameraComponent()->GetRelativeRotation();
	FVector currentLocation = GetFirstPersonCameraComponent()->GetRelativeLocation();

	targetLeanRotAmount = FMath::Clamp(currentRotation.Roll + rollAmount, -maxLeanRotationAmount, maxLeanRotationAmount);
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
	
}

bool AExMCharacter::CanStand()
{
	return true;
}
