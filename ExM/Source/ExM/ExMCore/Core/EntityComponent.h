#pragma once
#include "CoreMinimal.h"
#include "ExM/ExMCore/Buffables.h"
#include "ExM/ExMCore/Utils/DamageCalculators.h"
#include "EntityComponent.generated.h"

class AExMCharacter;

constexpr float COYOTE_TIME = 0.016667;
constexpr float CAN_STAND_DURATION = 0.01667f;

USTRUCT(BlueprintType)
struct FEntityComponent {
	GENERATED_BODY()
};

UENUM(BlueprintType)
enum EExMMovementMode {
	EXM_WALK,
	EXM_SPRINT,
	EXM_VAULT,
	EXM_JUMP,
	EXM_SLIDE,
	EXM_FALL,
};

UENUM(BlueprintType)
enum EStances {
	STANCE_STANDING,
	STANCE_CROUCHING
};

USTRUCT(BlueprintType)
struct FPlayerMovementComponent : public FEntityComponent {
	GENERATED_BODY()
	AExMCharacter* character;

	EExMMovementMode currentMovementMode;
	EExMMovementMode previousMovementMode;
	EStances     currentStance;
	
	float startFallHeight;
	float targetLeanRotAmount;
	float targetLeanLocAmount;
	float targetStanceCapsuleHeight;
	float targetStanceEyeHeight;
	bool wantsToStand;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Crouch")
	float crouchAlpha;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Crouch")
	float crouchAnimAlpha;

	FBuffableFloat movementSpeed;

	void ChangeMovementMode(EExMMovementMode newMovementMode)
	{
		previousMovementMode = currentMovementMode;
		currentMovementMode = newMovementMode;
	}
};

USTRUCT(BlueprintType)
struct FJumpComponent : public FEntityComponent {
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int maxJumps = 1;
	
	int currentJumps;
	
	float nextCoyoteTime;

	bool canJump;
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
	bool bWantsToJump;

	UPROPERTY(BlueprintReadWrite)
	bool bWantsToSprint;

	UPROPERTY(BlueprintReadWrite)
	bool bCancelSprint;

	UPROPERTY(BlueprintReadWrite)
	bool bCrouchInput;

	UPROPERTY(BlueprintReadWrite)
	bool bIsLeaning;

	UPROPERTY(BlueprintReadWrite)
	bool bIsFiring;
};

USTRUCT(BlueprintType)
struct FPlayerInputComponent : public FEntityComponent {

	GENERATED_BODY()

	FPlayerInputData inputData;
};

USTRUCT(BlueprintType)
struct FAIComponent : public FEntityComponent {
	GENERATED_BODY()
};



