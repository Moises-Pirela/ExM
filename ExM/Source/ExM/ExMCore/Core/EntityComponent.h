#pragma once
#include "CoreMinimal.h"
#include "ExM/ExMCore/Buffables.h"
#include "ExM/ExMCore/Utils/DamageCalculators.h"
#include "ExM/MovementStateMachine/MovementStateMachine.h"
#include "EntityComponent.generated.h"

class AExMCharacter;

USTRUCT(BlueprintType)
struct FEntityComponent {
	GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FPlayerMovementComponent : public FEntityComponent {
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
struct FDamageComponent : public FEntityComponent {
	GENERATED_BODY()
	FBuffableFloat damage;
	EDamageTypes   damageType;
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
struct FAttributesComponent : public FEntityComponent {
	GENERATED_BODY()
	FBuffableInt strength;
	FBuffableInt dexterity;
	FBuffableInt intelligence;
};

USTRUCT(BlueprintType)
struct FEquipmentComponent : public FEntityComponent {
	GENERATED_BODY()
	int equippedEntityId;
	int prevEquippedEntityId;
};

USTRUCT(BlueprintType)
struct FPlayerInputData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FVector2D moveDirection;

	UPROPERTY(BlueprintReadWrite)
	FVector2D lookDirection;

	UPROPERTY(BlueprintReadWrite)
	bool bIsJumping;

	UPROPERTY(BlueprintReadWrite)
	bool bIsSprinting;

	UPROPERTY(BlueprintReadWrite)
	bool bIsCrouching;

	UPROPERTY(BlueprintReadWrite)
	bool bIsLeaning;

	UPROPERTY(BlueprintReadWrite)
	bool bIsFiring;
};

USTRUCT()
struct FPlayerInputComponent : public FEntityComponent {

	GENERATED_BODY()

	FPlayerInputData inputData;
};

USTRUCT(BlueprintType)
struct FAIComponent : public FEntityComponent {
	GENERATED_BODY()
};



