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
#include "ExMCore/Components/ExMJumpComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AExMCharacter::AExMCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	jumpComponent = CreateDefaultSubobject<UExMJumpComponent>("JumpComponent");
}

void AExMCharacter::BeginPlay()
{
	Super::BeginPlay();

	currentStance = EStances::Standing;
}

void AExMCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

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

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AExMCharacter::Look);

		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &AExMCharacter::Sprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AExMCharacter::CancelSprint);
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

	if (currentMovementMode != Walk) return;

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

bool AExMCharacter::CanStand()
{
	return true;
}
