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

USTRUCT()
struct FWeaponComponent : public FEntityComponent {
	GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FInventoryItemSlot  {
	GENERATED_BODY()
	int configId;
	int stacks;
};

USTRUCT()
struct FInventoryComponent : public FEntityComponent {
	GENERATED_BODY()
	TArray<FInventoryItemSlot> inventory;
};

USTRUCT()
struct FEquipmentComponent : public FEntityComponent {
	GENERATED_BODY()
	int equippedEntityId;
	int prevEquippedEntityId;
};



