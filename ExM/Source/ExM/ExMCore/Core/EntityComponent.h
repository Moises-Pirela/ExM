#pragma once
#include "CoreMinimal.h"
#include "ExM/ExMCore/Buffables.h"
#include "ExM/MovementStateMachine/MovementStateMachine.h"
#include "EntityComponent.generated.h"

class AExMCharacter;

USTRUCT(BlueprintType)
struct FEntityComponent {
	GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FMovementStateComponent : public FEntityComponent {
	GENERATED_BODY()
	AExMCharacter* character;
	MovementStateMachine movementStateMachine;
};

USTRUCT(BlueprintType)
struct FHealthComponent : public FEntityComponent {
	GENERATED_BODY()
	FBuffableFloat health;
};

USTRUCT(BlueprintType)
struct FStatComponent : public FEntityComponent {
	GENERATED_BODY()
	FBuffableInt strength;
	FBuffableInt dexterity;
	FBuffableInt intelligence;
};

USTRUCT(BlueprintType)
struct FPlayerTag : public FEntityComponent {
	GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FWeaponComponent : public FEntityComponent {
	GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FInventoryItemSlot  {
	GENERATED_BODY()
	int configId;
	int stacks;
};

USTRUCT(BlueprintType)
struct FInventoryComponent : public FEntityComponent {
	GENERATED_BODY()
	TArray<FInventoryItemSlot> inventory;
};

USTRUCT(BlueprintType)
struct FEquipmentComponent : public FEntityComponent {
	GENERATED_BODY()
	int equippedEntityId;
	int prevEquippedEntityId;
};



