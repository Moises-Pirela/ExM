// © 2024 Necrotek Labs. All rights reserved. ExMORTALIS, including its title, logo, concept, storyline, and associated assets, is a trademark of Necrotek Labs. Unauthorized use, distribution, or reproduction of any part of this game or its materials is strictly prohibited. All other trademarks and trade names are the property of their respective owners. For inquiries, please contact necroteklabs@gmail.com.


#include "PlayerMovementSystem.h"

#include "ExM/ExMCharacter.h"
#include "ExM/ExMCore/Core/EntityComponent.h"

void UPlayerMovementSystem::Process(EntityContainer* entityContainer, float deltaTime) {

	if(entityContainer->PLAYER_ENTITY_ID == -1) return;

	FEntity&                 _playerEntity = entityContainer->GetPlayerEntity();
	FPlayerMovementComponent* _movementStateComponent = entityContainer->GetComponent<FPlayerMovementComponent>(_playerEntity.id);
	FPlayerInputComponent*   _inputComponent = entityContainer->GetComponent<FPlayerInputComponent>(_playerEntity.id);

	FVector2D _moveInput = _inputComponent->inputData.moveDirection;
	_movementStateComponent->character->AddMovementInput(_movementStateComponent->character->GetActorForwardVector(), _moveInput.Y);
	_movementStateComponent->character->AddMovementInput(_movementStateComponent->character->GetActorRightVector(), _moveInput.X);

	_inputComponent->inputData.moveDirection = FVector2D::Zero();

	FVector2D _lookInput = _inputComponent->inputData.lookDirection;
	_movementStateComponent->character->AddControllerYawInput(_lookInput.X);
	_movementStateComponent->character->AddControllerPitchInput(_lookInput.Y);
	
	_inputComponent->inputData.lookDirection = FVector2D::Zero();
}

ESystemTickType UPlayerMovementSystem::GetSystemTickType() {
	return ESystemTickType::SYSTEM_TICK;
}
