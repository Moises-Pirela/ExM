#pragma once
#include "CoreMinimal.h"
#include "ExM/ExMCore/Buffables.h"
#include "ExM/MovementStateMachine/MovementStateMachine.h"
#include "EntityComponent.generated.h"

class AExMCharacter;

USTRUCT()
struct FEntityComponent {
	GENERATED_BODY()
};

USTRUCT()
struct FMovementStateComponent : public FEntityComponent {
	GENERATED_BODY()
	AExMCharacter* character;
	MovementStateMachine movementStateMachine;
};

USTRUCT()
struct FHealthComponent : public FEntityComponent {
	GENERATED_BODY()
	FBuffableFloat health;
};

USTRUCT()
struct FStatComponent : public FEntityComponent {
	GENERATED_BODY()
	FBuffableInt strength;
	FBuffableInt dexterity;
	FBuffableInt intelligence;
};

USTRUCT()
struct FPlayerTag : public FEntityComponent {
	GENERATED_BODY()
};
