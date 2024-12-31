#pragma once

#include "CoreMinimal.h"
#include "ExM/ExMCore/Components/BaseComponent.h"
#include "Entity.generated.h"

class UEntityConfig;
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

	int value;

	FComponentFlags(): value(0)
	{
	}

	FComponentFlags(const int* componentTypes, const int32 count): value(0)
	{
		for (int i = 0; i < count; i++)
		{
			uint32 type = (uint32)componentTypes[i];

			AddFlag(type);
		}
	}

	FComponentFlags(const EComponentTypes* componentTypes, const int32 count): value(0)
	{
		for (int i = 0; i < count; i++)
		{
			uint32 type = (uint32)componentTypes[i];

			AddFlag(type);
		}
	}

	void AddFlag(const int flag)
	{
		value |= flag; 
	}

	void RemoveFlag(const int flag)
	{
		value &= ~flag; 
	}

	bool HasFlag(const int flag) const
	{
		return (value & flag) != 0; 
	}

	bool MatchesSignature(const FComponentFlags flags)
	{
		return (value & flags.value) == value;
	}
};

struct FEntity {

	FEntity() {
		id = -1;
		entityFlags = FEntityFlags();
		componentSignature = FComponentFlags();
	}
	
	int id;

	FEntityFlags entityFlags;
	FComponentFlags componentSignature;

	static FEntity Empty() {
		return FEntity();
	}

	bool HasComponent(const int flag)
	{
		return componentSignature.HasFlag(flag);
	}
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UEntity : public UActorComponent
{
	GENERATED_BODY()

public:
	UEntity() { entityId = -1; };
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int entityId;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UEntityConfig* entityConfig;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsStartingEntity;

	void SetupEntity();
	
private:
	virtual void BeginPlay() override;
	virtual void DestroyComponent(bool bPromoteChildren) override;
};




