#pragma once

#include "CoreMinimal.h"
#include "ExM/ExMCore/Components/BaseComponent.h"
#include "ExM/ExMCore/Utils/Exmortalis.h"
#include "ComponentArray.generated.h"

struct FEntityComponent;

USTRUCT(BlueprintType)
struct FComponentArray
{
	GENERATED_BODY()

	FEntityComponent* components[MAX_ENTITY_COUNT];

	void AddComponent(FEntityComponent* component, int entityId)
	{
		components[entityId] = component;
	}

	void RemoveComponent(int entityId)
	{
		components[entityId] = nullptr;
	}
};
