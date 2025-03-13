// © 2024 Necrotek Labs. All rights reserved. ExMORTALIS, including its title, logo, concept, storyline, and associated assets, is a trademark of Necrotek Labs. Unauthorized use, distribution, or reproduction of any part of this game or its materials is strictly prohibited. All other trademarks and trade names are the property of their respective owners. For inquiries, please contact necroteklabs@gmail.com.


#include "LeanSystem.h"

#include "ExM/ExMCharacter.h"
#include "GameFramework/SpringArmComponent.h"

void ULeanSystem::Init(EntityContainer* entityContainer)
{
}

void ULeanSystem::Process(EntityContainer* entityContainer, float deltaTime)
{
	if (entityContainer->PLAYER_ENTITY_ID == -1) return;

	FEntity& _playerEntity = entityContainer->GetPlayerEntity();
	FPlayerMovementComponent* _movementStateComponent = entityContainer->GetComponent<FPlayerMovementComponent>(
		_playerEntity.id);
	FPlayerInputComponent* _inputComponent = entityContainer->GetComponent<FPlayerInputComponent>(_playerEntity.id);

	float _targetLeanRotAmount = _inputComponent->inputData.targetLeanRotAmount;
	float _targetLeanLocAmount = _inputComponent->inputData.targetLeanLocAmount;

	auto _cameraRoot = _movementStateComponent->character->GetCameraRoot();
	auto _meshRoot = _movementStateComponent->character->GetMeshRoot();
	
	FRotator targetRotation = FRotator(_cameraRoot->GetRelativeRotation().Pitch, _cameraRoot->GetRelativeRotation().Yaw,
									   _targetLeanRotAmount);
	FRotator lerpedTarget = FMath::RInterpTo(_cameraRoot->GetRelativeRotation(), targetRotation, deltaTime, 10);
	_cameraRoot->SetRelativeRotation(lerpedTarget);
	_meshRoot->SetRelativeRotation(lerpedTarget);
	FVector targetLocation = FVector(0, _targetLeanLocAmount, _cameraRoot->GetRelativeLocation().Z);
	FVector lerpedLocTarget = FMath::VInterpTo(_cameraRoot->GetRelativeLocation(), targetLocation, deltaTime, 10);
	_cameraRoot->SetRelativeLocation(lerpedLocTarget);
	_meshRoot->SetRelativeLocation(lerpedLocTarget);
}

ESystemTickType ULeanSystem::GetSystemTickType()
{
	return SYSTEM_TICK;
}
