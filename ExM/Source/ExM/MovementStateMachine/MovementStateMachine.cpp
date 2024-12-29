#include "MovementStateMachine.h"

#include "ExM/ExMCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

MovementStateMachine::MovementStateMachine(): currentMovementMode(EXM_WALK)
{
	stateDataMap[EXM_WALK] = StateData(5.0f, 0.0f, true);
	stateDataMap[EXM_SPRINT] = StateData(10.0f, 5.0f, false);
	stateDataMap[EXM_SLIDE] = StateData(8.0f, 10.0f, false);
	stateDataMap[EXM_VAULT] = StateData(0.0f, 0.0f, true);
	stateDataMap[EXM_JUMP] = StateData(0.0f, 10.0f, true);

	transitionRulesMap[EExMMovementMode::EXM_WALK] = [](EExMMovementMode toState)
	{
		return toState == EExMMovementMode::EXM_SPRINT || toState == EXM_JUMP;
	};
	transitionRulesMap[EExMMovementMode::EXM_SPRINT] = [](EExMMovementMode toState)
	{
		return toState == EExMMovementMode::EXM_WALK || toState == EXM_JUMP || toState == EXM_VAULT;
	};
	transitionRulesMap[EExMMovementMode::EXM_SLIDE] = [](EExMMovementMode toState)
	{
		return toState == EExMMovementMode::EXM_WALK;
	};
	transitionRulesMap[EExMMovementMode::EXM_VAULT] = [](EExMMovementMode toState)
	{
		return toState == EExMMovementMode::EXM_WALK;
	};
	transitionRulesMap[EExMMovementMode::EXM_JUMP] = [](EExMMovementMode toState)
	{
		return toState == EExMMovementMode::EXM_WALK || toState == EXM_VAULT;
	};

	//ENTER STATE

	enterStateMap[EExMMovementMode::EXM_WALK] = [](AExMCharacter* character)
	{
		character->GetCharacterMovement()->MaxWalkSpeed = character->walkSpeed;
	};
	enterStateMap[EExMMovementMode::EXM_SPRINT] = [](AExMCharacter* character)
	{
		character->GetCharacterMovement()->MaxWalkSpeed = character->sprintSpeed;
	};
	enterStateMap[EExMMovementMode::EXM_SLIDE] = [](AExMCharacter* character)
	{
		character->GetWorldTimerManager().ClearTimer(character->sprintChargeTimerHandle);
		character->GetController()->SetIgnoreMoveInput(true);
	};
	enterStateMap[EExMMovementMode::EXM_VAULT] = [](AExMCharacter* character)
	{
		character->vaultStartLocation = character->GetActorLocation();
		character->vaultTimeline.PlayFromStart();
	};
	enterStateMap[EExMMovementMode::EXM_JUMP] = [](AExMCharacter* character)
	{
		//
	};

	//EXIT STATE

	exitStateMap[EExMMovementMode::EXM_WALK] = [](AExMCharacter* character)
	{
	};
	exitStateMap[EExMMovementMode::EXM_SPRINT] = [](AExMCharacter* character)
	{
	};
	exitStateMap[EExMMovementMode::EXM_SLIDE] = [](AExMCharacter* character)
	{
	};
	exitStateMap[EExMMovementMode::EXM_VAULT] = [](AExMCharacter* character)
	{
	};
	exitStateMap[EExMMovementMode::EXM_JUMP] = [](AExMCharacter* character)
	{
	};
}

bool MovementStateMachine::TransitionToState(EExMMovementMode newState, AExMCharacter* character)
{
	if (!transitionRulesMap[newState](newState)) return false;

	exitStateMap[currentMovementMode](character);

	enterStateMap[newState](character);

	currentMovementMode = newState;
	
	return true;
}

void MovementStateMachine::Update()
{

}
