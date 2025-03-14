// © 2024 Necrotek Labs. All rights reserved. ExMORTALIS, including its title, logo, concept, storyline, and associated assets, is a trademark of Necrotek Labs. Unauthorized use, distribution, or reproduction of any part of this game or its materials is strictly prohibited. All other trademarks and trade names are the property of their respective owners. For inquiries, please contact necroteklabs@gmail.com.


#include "PlayerMovementSystem.h"

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "ExM/ExMCharacter.h"
#include "ExM/ExMCore/Configs/EntityConfig.h"
#include "ExM/ExMCore/Configs/ComponentConfigs/PlayerMovementComponentConfig.h"
#include "ExM/ExMCore/Core/EntityComponent.h"
#include "ExM/ExMCore/Utils/Logger.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPlayerMovementSystem::Init(EntityContainer* entityContainer)
{
}

void UPlayerMovementSystem::Process(EntityContainer* entityContainer, float deltaTime)
{
	if (entityContainer->PLAYER_ENTITY_ID == -1) return;

	FEntity& _playerEntity = entityContainer->GetPlayerEntity();
	FPlayerMovementComponent* _movementStateComponent = entityContainer->GetComponent<FPlayerMovementComponent>(
		_playerEntity.id);
	FPlayerInputComponent* _inputComponent = entityContainer->GetComponent<FPlayerInputComponent>(_playerEntity.id);
	FJumpComponent* _jumpComponent = entityContainer->GetComponent<FJumpComponent>(_playerEntity.id);

	FVector2D _moveInput = _inputComponent->inputData.moveDirection;
	_movementStateComponent->character->AddMovementInput(_movementStateComponent->character->GetActorForwardVector(),
	                                                     _moveInput.Y);
	_movementStateComponent->character->AddMovementInput(_movementStateComponent->character->GetActorRightVector(),
	                                                     _moveInput.X);

	_inputComponent->inputData.moveDirection = FVector2D::Zero();

	FVector2D _lookInput = _inputComponent->inputData.lookDirection;
	_movementStateComponent->character->AddControllerYawInput(_lookInput.X);
	_movementStateComponent->character->AddControllerPitchInput(_lookInput.Y);

	_inputComponent->inputData.lookDirection = FVector2D::Zero();

	//------------ JUMP

	bool _bCoyoteTimeActive = _jumpComponent->nextCoyoteTime > GetWorld()->GetTimeSeconds();
	bool _bHasJumpsAvailable = _jumpComponent->currentJumps < _jumpComponent->maxJumps;
	_jumpComponent->canJump = _bHasJumpsAvailable || _bCoyoteTimeActive;

	auto movementConfig = _playerEntity.config->GetComponentConfig<UPlayerMovementComponentConfig>();

	if (_inputComponent->inputData.bWantsToJump)
	{
		if (_jumpComponent->canJump)
		{
			_movementStateComponent->character->Jump();
		}

		_inputComponent->inputData.bWantsToJump = false;
	}

	if (_inputComponent->inputData.bWantsToSprint)
	{
		if (_movementStateComponent->currentStance == STANCE_STANDING)
		{
			_movementStateComponent->ChangeMovementMode(EXM_SPRINT);
		}
		else
		{
			_inputComponent->inputData.bCancelSprint = true;
		}
	}

	if (_inputComponent->inputData.bCancelSprint)
	{
		_movementStateComponent->ChangeMovementMode(EXM_WALK);
		_inputComponent->inputData.bWantsToSprint = false;
		_inputComponent->inputData.bCancelSprint = false;
	}

	if (_inputComponent->inputData.bCrouchInput)
	{
		if (_movementStateComponent->currentStance == EStances::STANCE_STANDING)
		{
			_movementStateComponent->currentStance = EStances::STANCE_CROUCHING;
			_movementStateComponent->character->GetCharacterMovement()->MaxWalkSpeed = _movementStateComponent->
				movementSpeed.GetValue() * movementConfig->crouchModifier;
			_movementStateComponent->targetStanceCapsuleHeight = movementConfig->crouchCapsuleHeight;
		}
		else
		{
			_movementStateComponent->wantsToStand = true;
		}

		_inputComponent->inputData.bCrouchInput = false;
	}

	if (_movementStateComponent->wantsToStand)
	{
		TryStand(movementConfig, _movementStateComponent);
	}

	_movementStateComponent->crouchAlpha = _movementStateComponent->targetStanceCapsuleHeight / _movementStateComponent
		->character->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
	float easedTarget = EaseInOutSine(_movementStateComponent->crouchAlpha);
	float lerpedStanceTarget = FMath::Lerp(
		_movementStateComponent->character->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight(),
		_movementStateComponent->targetStanceCapsuleHeight,
		easedTarget * deltaTime * movementConfig->stanceChangeSpeed);
	_movementStateComponent->character->GetCapsuleComponent()->SetCapsuleHalfHeight(lerpedStanceTarget);

	if (_movementStateComponent->currentStance == STANCE_CROUCHING)
	{
		_movementStateComponent->crouchAnimAlpha = _movementStateComponent->crouchAlpha;
	}
	else
	{
		_movementStateComponent->crouchAnimAlpha = 0;
	}

	//-------------- CHECK MOVEMENT STATES

	if (_movementStateComponent->character->GetCharacterMovement()->MovementMode == MOVE_Falling &&
		_movementStateComponent->currentMovementMode != EXM_FALL)
	{
		_movementStateComponent->ChangeMovementMode(EXM_FALL);
		_jumpComponent->nextCoyoteTime = GetWorld()->GetTimeSeconds() + COYOTE_TIME;
	}

	if (_movementStateComponent->character->GetCharacterMovement()->MovementMode != MOVE_Falling &&
		_movementStateComponent->currentMovementMode == EXM_FALL)
	{
		_movementStateComponent->ChangeMovementMode(EXM_WALK);
	}

	float finalMovementSpeed = _movementStateComponent->movementSpeed.GetValue();

	if (_movementStateComponent->currentMovementMode == EXM_SPRINT)
	{
		finalMovementSpeed *= movementConfig->sprintModifier;
	}

	if (_movementStateComponent->currentStance == EStances::STANCE_CROUCHING)
	{
		finalMovementSpeed *= movementConfig->crouchModifier;
	}

	_movementStateComponent->character->GetCharacterMovement()->MaxWalkSpeed = finalMovementSpeed;
}

ESystemTickType UPlayerMovementSystem::GetSystemTickType()
{
	return ESystemTickType::SYSTEM_TICK;
}

void UPlayerMovementSystem::TryStand(UPlayerMovementComponentConfig* config,
                                     FPlayerMovementComponent* movementComponent) const
{
	float _stanceHeightDiff = config->crouchCapsuleHeight - config->standCapsuleHeight;
	float _z = movementComponent->character->GetActorLocation().Z + config->crouchCapsuleHeight;
	float alpha = movementComponent->targetStanceCapsuleHeight / movementComponent->character->GetCapsuleComponent()->
		GetUnscaledCapsuleHalfHeight();
	float _lerpedHeight = (FMath::Lerp(0, _stanceHeightDiff, alpha) * 1.1) + _z;
	FVector _startTraceLocation = FVector(movementComponent->character->GetActorLocation().X,
	                                      movementComponent->character->GetActorLocation().Y, _z);
	FVector _endTraceLocation = FVector(movementComponent->character->GetActorLocation().X,
	                                    movementComponent->character->GetActorLocation().Y, _lerpedHeight);

	FHitResult hit;
	FCollisionQueryParams params(NAME_None, true);
	FCollisionShape sphereShape = FCollisionShape::MakeSphere(
		movementComponent->character->GetCapsuleComponent()->GetUnscaledCapsuleRadius());

	if (GetWorld()->SweepSingleByChannel(hit, _startTraceLocation, _endTraceLocation, FQuat::Identity, ECC_Visibility,
	                                     sphereShape, params)) {
		return;
	}

	movementComponent->currentStance = EStances::STANCE_STANDING;
	movementComponent->targetStanceCapsuleHeight = config->standCapsuleHeight;
	movementComponent->wantsToStand = false;
}
