// Copyright Epic Games, Inc. All Rights Reserved.

#include "ExMCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Chaos/Deformable/ChaosDeformableCollisionsProxy.h"
#include "Components/TimelineComponent.h"
#include "Engine/LocalPlayer.h"
#include "ExMCore/Components/ExmEquipmentComponent.h"
#include "ExMCore/Components/ExMHealthComponent.h"
#include "ExMCore/Components/ExMInteractionComponent.h"
#include "ExMCore/Components/ExMJumpComponent.h"
#include "ExMCore/Components/ExmStatsComponent.h"
#include "ExMCore/Utils/DamageCalculators.h"
#include "ExMCore/Utils/Exmortalis.h"
#include "ExMCore/Utils/MathUtils.h"
#include "ExMCore/Utils/StatHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "MovementStateMachine/MovementStateMachine.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AExMCharacter::AExMCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

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
	statsComponent = GetComponentByClass<UExmStatsComponent>();

	walkSpeed = CalculateMovementSpeed(statsComponent->attributes[ATTRIBUTE_DEXTERITY].GetValue(), walkSpeed, 1);
	sprintSpeed = walkSpeed * 2.5f;
	crouchSpeed = walkSpeed * 0.7f;
	GetCharacterMovement()->JumpZVelocity = CalculateJumpHeight(statsComponent->attributes[ATTRIBUTE_STRENGTH].GetValue(),
	                                                            statsComponent->attributes[ATTRIBUTE_DEXTERITY].GetValue(),
	                                                            GetCharacterMovement()->JumpZVelocity, 1);

	statsComponent->Init();

	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;

	FOnTimelineFloat ProgressFunction;
	ProgressFunction.BindUFunction(this, FName("OnVaultProgress"));

	FOnTimelineEvent FinishedFunction;
	FinishedFunction.BindUFunction(this, FName("OnVaultFinished"));

	vaultTimeline.AddInterpFloat(VaultCurve, ProgressFunction);
	vaultTimeline.SetTimelineFinishedFunc(FinishedFunction);
	vaultTimeline.SetTimelineLength(1.0f);
	vaultTimeline.SetPlayRate(2.0f);

	vaultTimeline.SetLooping(false);
}

void AExMCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(healthComponent->IsDead())
	{
		targetLeanRotAmount = -60;
		targetLeanLocAmount = 0;
	}

	//LEAN
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
	crouchAlpha = targetStanceCapsuleHeight / GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
	float easedTarget = EaseInOutSine(crouchAlpha);
	float lerpedStanceTarget = FMath::Lerp(GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight(),
	                                       targetStanceCapsuleHeight, easedTarget * DeltaSeconds * stanceChangeSpeed);
	GetCapsuleComponent()->SetCapsuleHalfHeight(lerpedStanceTarget);

	if(currentStance == STANCE_CROUCHING)
	{
		crouchAnimAlpha = crouchAlpha;
	} else
	{
		crouchAnimAlpha = 0;
	}

	vaultTimeline.TickTimeline(DeltaSeconds);
}

void AExMCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	float fallHeightDiff = startFallHeight - GetActorLocation().Z;

	if(fallHeightDiff > FALL_DAMAGE_THRESHOLD)
	{
		FDamageData damage;

		damage.baseDamage = fallHeightDiff;
		damage.damageType = EDamageTypes::DAMAGE_TYPE_FALL;

		healthComponent->TakeDamage(damage);
	}


	ResetCoyoteTime();
	jumpComponent->ResetJump();
}

void AExMCharacter::Jump()
{
	if(TryVault()) return;

	Super::Jump();

	jumpComponent->currentJumpCount = FMath::Clamp(jumpComponent->currentJumpCount + 1, 0, jumpComponent->maxJumpCount);
}

void AExMCharacter::StopJumping()
{
	Super::StopJumping();
}

void AExMCharacter::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PrevMovementMode, PreviousCustomMode);

	if(GetCharacterMovement()->MovementMode == MOVE_Falling)
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

void AExMCharacter::OnVaultProgress(float Value)
{
	FVector newLocation = FMath::Lerp(vaultStartLocation, vaultEndLocation, Value);
	SetActorLocation(newLocation);
}

void AExMCharacter::OnVaultFinished()
{
	UE_LOG(LogTemp, Log, TEXT("Vault Completed"));
}

void AExMCharacter::StartVault(FVector TargetLocation)
{	
}

bool AExMCharacter::TryVault()
{
	FVector _start = GetActorLocation() + FVector(0, 0, 100.0f);
	FVector _forward = GetActorForwardVector();
	FVector _end = _start + _forward * 145.0f;

	FHitResult            _hitResult;
	FCollisionQueryParams _queryParams;
	_queryParams.AddIgnoredActor(this);

	UCapsuleComponent* _capsule = GetCapsuleComponent();
	float              _capsuleRadius = _capsule->GetScaledCapsuleRadius();
	float              _capsuleHalfHeight = _capsule->GetScaledCapsuleHalfHeight();

	FCollisionShape _capsuleShape = FCollisionShape::MakeCapsule(_capsuleRadius, _capsuleHalfHeight);

	bool _bHit = GetWorld()->SweepSingleByChannel(
		_hitResult,
		_start,
		_end,
		FQuat::Identity,
		ECC_Visibility,
		_capsuleShape,
		_queryParams
	);

	DrawDebugCapsule(GetWorld(), _start, _capsuleHalfHeight, _capsuleRadius, FQuat::Identity, _bHit ? FColor::Red : FColor::Green, false, 2.0f);

	if(!_hitResult.bBlockingHit) return false;

	// Check if the surface is walkable
	//if (!GetCharacterMovement()->IsWalkable(_hitResult)) return false;

	FVector         _hitPoint = _hitResult.ImpactPoint;
	FVector         _hitNormal = _hitResult.ImpactNormal;
	FCollisionShape _sphereShape = FCollisionShape::MakeSphere(30);

	FVector _sphereStart = _hitPoint + FVector(0, 0, _capsuleHalfHeight);
	FVector _sphereEnd = _sphereStart + FVector(0, 0, 120.0f);

	bool _bSphereTrace = GetWorld()->SweepSingleByChannel(
		_hitResult,
		_sphereStart,
		_sphereEnd,
		FQuat::Identity,
		ECC_Visibility,
		_sphereShape,
		_queryParams
	);

	DrawDebugLine(GetWorld(), _sphereStart, _sphereEnd, FColor::Green, false, 2.0f, 0, 1.0f);
	DrawDebugSphere(GetWorld(), _sphereEnd, _sphereShape.GetSphereRadius(), 12, FColor::Blue, false, 2.0f);

	if(_bSphereTrace && _hitResult.bBlockingHit) return false;

	FVector _vaultTarget = _hitPoint + FVector(0, 0, _capsuleHalfHeight / 2);

	FVector _capsuleStart = FVector(_vaultTarget.X, _vaultTarget.Y, _vaultTarget.Z + 15);
	FVector _capsuleEnd = FVector(_vaultTarget.X, _vaultTarget.Y, _vaultTarget.Z + _capsuleHalfHeight);

	bool _bCapsuleSphereTrace = GetWorld()->SweepSingleByChannel(
		_hitResult,
		_capsuleStart,
		_capsuleEnd,
		FQuat::Identity,
		ECC_Visibility,
		FCollisionShape::MakeSphere(_capsuleRadius),
		_queryParams
	);

	if(_bCapsuleSphereTrace && _hitResult.bBlockingHit) return false;

	DrawDebugCapsule(GetWorld(), _capsuleStart, _capsuleHalfHeight, _capsuleRadius, FQuat::Identity, FColor::Yellow, false, 2.0f);

	_vaultTarget += FVector::UpVector * _capsuleHalfHeight + 10;

	vaultEndLocation = _vaultTarget;

	vaultTimeline.PlayFromStart();

	return true;
}


void AExMCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AExMCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AExMCharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AExMCharacter::Move);
		EnhancedInputComponent->BindAction(PrimaryFireAction, ETriggerEvent::Started, this,
		                                   &AExMCharacter::PrimaryFire);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AExMCharacter::Look);

		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &AExMCharacter::Sprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AExMCharacter::CancelSprint);

		EnhancedInputComponent->BindAction(LeanAction, ETriggerEvent::Triggered, this, &AExMCharacter::Lean);
		EnhancedInputComponent->BindAction(LeanAction, ETriggerEvent::Completed, this, &AExMCharacter::StopLean);

		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &AExMCharacter::DoCrouch);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AExMCharacter::StartStand);
	}
}

FVector AExMCharacter::GetVelocityVars(FVector outLagPos)
{
	const float velocityForward = FVector::DotProduct(GetVelocity(), GetActorForwardVector()) / sprintSpeed;
	const float velocityRight = FVector::DotProduct(GetVelocity(), GetActorRightVector()) / sprintSpeed;
	const float velocityUp = FVector::DotProduct(GetVelocity(), GetActorUpVector()) / -GetCharacterMovement()->
	JumpZVelocity;

	FVector velocity = FVector(velocityRight, velocityForward, velocityUp) * 2;
	velocity = velocity.GetClampedToSize(0, 4);
	const float interpSpeed = (1 / GetWorld()->GetDeltaSeconds()) / 6;

	outLagPos = FMath::VInterpTo(outLagPos, velocity, GetWorld()->GetDeltaSeconds(), interpSpeed);

	FRotator jumpFeedbackRotator = FRotator(0, outLagPos.Z * -2.0f, 0);
	FVector  jumpFeedbackVector = FVector(outLagPos.Z * -0.5f, 0, 0);

	float deltaSecs = GetWorld()->GetDeltaSeconds();
	float airInterpSpeed = (1 / deltaSecs) / 6.0f;

	inAirTilt = FMath::RInterpTo(inAirTilt, jumpFeedbackRotator, deltaSecs, airInterpSpeed);

	inAirOffSet = FMath::VInterpTo(inAirOffSet, jumpFeedbackVector, deltaSecs, airInterpSpeed);

	return outLagPos;
}

void AExMCharacter::GetLookInputVars(FRotator camRotPrev)
{
	FRotator deltaRot = (GetControlRotation() - GetActorRotation()).GetNormalized();

	float normalizedPitch = NormalizeToRange(deltaRot.Pitch, -90, 90);

	float yLerp = FMath::Lerp(3.0f, -3.0f, normalizedPitch);
	float zLerp = FMath::Lerp(2.0f, -2.0f, normalizedPitch);

	pitchOffsetPos = FVector(0, yLerp, zLerp);

	normalizedPitch = NormalizeToRange(normalizedPitch, 0.0f, 0.5f);
	normalizedPitch = FMath::Clamp(normalizedPitch, 0.0f, 1.0f);

	float targetXLoc = FMath::Lerp(35.0f, 0.0f, normalizedPitch);

	FVector relativeLocation = FPRoot->GetRelativeLocation();

	FVector newLocation = FVector(targetXLoc, relativeLocation.Y, relativeLocation.Z);

	FPRoot->SetRelativeLocation(newLocation);

	camRotCurrent = FirstPersonCameraComponent->GetComponentRotation();

	FRotator camDeltaRot = (camRotCurrent - camRotPrev).GetNormalized();

	float clampedCamPitch = FMath::Clamp(camDeltaRot.Pitch * -1.0f, -5.0f, 5.0f);
	float clampedCamYaw = FMath::Clamp(camDeltaRot.Yaw, -5.0f, 5.0f);

	camDeltaRot.Roll = clampedCamPitch;
	camDeltaRot.Yaw = clampedCamYaw;
	camDeltaRot.Pitch = 0;

	float interpSpeed = (1 / GetWorld()->GetDeltaSeconds()) / 20.0f;

	camRotRate = FMath::RInterpTo(camRotRate, camDeltaRot, GetWorld()->GetDeltaSeconds(), interpSpeed);

	float lerpedRoll = FMath::Lerp(-10.0f, 10.0f, NormalizeToRange(camRotRate.Roll, -5.0f, 5.0));
	float lerpedYaw = FMath::Lerp(-6.0f, 6.0f, NormalizeToRange(camRotRate.Yaw, -5.0f, 5.0));

	camRotOffset = FVector(lerpedYaw, 0, lerpedRoll);
}

void AExMCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if(Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
		CheckStopSprint(MovementVector.Y);
	}
}

void AExMCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if(Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AExMCharacter::Sprint(const FInputActionValue& value)
{
	//TODO: Check if reloading

	if(currentStance == EStances::STANCE_CROUCHING)
	{
		StartStand();
	}

	GetCharacterMovement()->MaxWalkSpeed = sprintSpeed;
	GetWorld()->GetTimerManager().SetTimer(sprintChargeTimerHandle, this, &AExMCharacter::IncreaseSprintCharge, 0.1f, true);
}

void AExMCharacter::CancelSprint()
{

	GetWorldTimerManager().ClearTimer(sprintChargeTimerHandle);
	sprintCharge = 0;
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
}

void AExMCharacter::StartSlide()
{
	GetWorldTimerManager().ClearTimer(sprintChargeTimerHandle);
	GetController()->SetIgnoreMoveInput(true);
	SlideTL();
}

void AExMCharacter::CheckStopSprint(float inAxis)
{
	if(inAxis < 0.5f)
	{
		CancelSprint();
	}
}

void AExMCharacter::IncreaseSprintCharge()
{
	if(sprintCharge < 1.0f) sprintCharge = FMath::Clamp(sprintCharge + 0.1f, 0.0f, 1.0f);
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(sprintChargeTimerHandle);
	}
}

void AExMCharacter::DoCrouch()
{
	if(currentStance == EStances::STANCE_STANDING)
	{
		if(true)
		{
			StartSlide();
		} else
		{
			currentStance = EStances::STANCE_CROUCHING;
			GetCharacterMovement()->MaxWalkSpeed = crouchSpeed;
			targetStanceCapsuleHeight = crouchCapsuleHeight;
			GetWorld()->GetTimerManager().ClearTimer(checkCanStandTimerHandle);
		}
	}
	else
	{
		StartStand();
	}
}

void AExMCharacter::StartStand()
{
	if(currentStance == EStances::STANCE_CROUCHING)
	{
		
		GetWorld()->GetTimerManager().ClearTimer(checkCanStandTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(checkCanStandTimerHandle, this, &AExMCharacter::TryStand,
		                                       CAN_STAND_DURATION, true);
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
	float   _stanceHeightDiff = crouchCapsuleHeight - standCapsuleHeight;
	float   _z = GetActorLocation().Z + crouchCapsuleHeight;
	float   alpha = targetStanceCapsuleHeight / GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
	float   _lerpedHeight = (FMath::Lerp(0, _stanceHeightDiff, alpha) * 1.1) + _z;
	FVector _startTraceLocation = FVector(GetActorLocation().X, GetActorLocation().Y, _z);
	FVector _endTraceLocation = FVector(GetActorLocation().X, GetActorLocation().Y, _lerpedHeight);

	FHitResult            hit;
	FCollisionQueryParams params(NAME_None, false, this);
	FCollisionShape       sphereShape = FCollisionShape::MakeSphere(GetCapsuleComponent()->GetUnscaledCapsuleRadius());

	if(GetWorld()->SweepSingleByChannel(hit, _startTraceLocation, _endTraceLocation, FQuat::Identity, ECC_Visibility,
	                                    sphereShape, params))
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
	FVector  currentLocation = GetFirstPersonCameraComponent()->GetRelativeLocation();

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
	if(interactComponent->grabbedComponent != nullptr)
	{
		UPrimitiveComponent* grabbedComp = interactComponent->grabbedComponent;

		interactComponent->physicsHandleComponent->ReleaseComponent();
		grabbedComp->SetPhysicsLinearVelocity(FVector::Zero());

		FVector throwDirection = GetActorForwardVector();
		interactComponent->grabbedComponent = nullptr;
		interactComponent->currentInteractionType = INTERACTION_NONE;

		float throwStrength = CalculateThrowStrength(statsComponent->attributes[ATTRIBUTE_STRENGTH].GetValue(), grabbedComp->GetMass(), 1);

		grabbedComp->AddImpulse(throwDirection * throwStrength, NAME_None, true);
	} else
	{
		equipmentComponent->FireWeapon();
	}
}

void AExMCharacter::SecondaryFire()
{
	equipmentComponent->SecondaryFire();
}
