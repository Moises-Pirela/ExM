#pragma once


class AExMCharacter;

UENUM(BlueprintType)
enum EExMMovementMode {
	EXM_WALK,
	EXM_SPRINT,
	EXM_VAULT,
	EXM_JUMP,
	EXM_SLIDE,
};

struct StateData {
	float baseSpeed;
	float staminaCost;
	bool  canTransitionWhileAirborne;
};

typedef void (*StateEnterExit)(AExMCharacter* character);
typedef bool (*StateTransition)(EExMMovementMode newMode);

struct MovementStateMachine {
	EExMMovementMode                        currentMovementMode;
	TMap<EExMMovementMode, StateData>       stateDataMap;
	TMap<EExMMovementMode, StateTransition> transitionRulesMap;
	TMap<EExMMovementMode, StateEnterExit>  enterStateMap;
	TMap<EExMMovementMode, StateEnterExit>  exitStateMap;

	MovementStateMachine();

	bool TransitionToState(EExMMovementMode newState, AExMCharacter* character);
	void Update();
};
