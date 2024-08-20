#pragma once

#include "CoreMinimal.h"
#include "ExM/ExMCore/Components/BaseComponent.h"
#include "Entity.generated.h"

class UBaseComponent;

UENUM(BlueprintType)
enum EEntityState : uint8
{
	ENTITY_STATE_ACTIVE = 0,
	ENTITY_STATE_DEAD,
	ENTITY_STATE_INACTIVE,
	
	ENTITY_STATE_MAX
};

USTRUCT(BlueprintType)
struct FEntityFlags
{
	GENERATED_BODY()

	uint8 value;

	FEntityFlags(): value(ENTITY_STATE_INACTIVE)
	{
	}
	
	void AddFlag(const uint8 flag)
	{
		value |= (1 << flag);
	}

	void RemoveFlag(const uint8 flag)
	{
		value &= ~(1 << flag);
	}

	bool HasFlag(uint8 flag)
	{
		return (value & (1 << flag)) != 0;
	}
	
};

USTRUCT(BlueprintType)
struct FComponentFlags
{
	GENERATED_BODY()

	uint32 value;

	FComponentFlags(): value(0)
	{
	}

	FComponentFlags(const EComponentTypes* componentTypes, const int32 count): value(0)
	{
		for (int i = 0; i < count; i++)
		{
			uint32 type = (uint32)componentTypes[i];

			AddFlag(type);
		}
	}

	void AddFlag(const uint32 flag)
	{
		value |= (1 << flag);
	}

	void RemoveFlag(const uint32 flag)
	{
		value &= ~(1 << flag);
	}

	bool HasFlag(const uint32 flag)
	{
		return (value & (1 << flag)) != 0;
	}
	
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UEntity : public UActorComponent
{
	GENERATED_BODY()

public:
	UEntity(): entityFlags(nullptr), componentSignature(nullptr) { entityId = -1; };

	int entityId;

	FEntityFlags *entityFlags;
	FComponentFlags *componentSignature;

	TArray<UBaseComponent*> GetComponents()
	{
		auto components = TArray<UBaseComponent*>{};

		GetOwner()->GetComponents<UBaseComponent*>(components);
		
		return components;
	}
};


