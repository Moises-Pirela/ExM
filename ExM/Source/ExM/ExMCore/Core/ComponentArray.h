#pragma once
#include "EntityContainer.h"
#include "ExM/ExMCore/Components/BaseComponent.h"

#include "ComponentArray.generated.h"

class UBaseComponent;

USTRUCT(BlueprintType)
struct FComponentArray
{
	GENERATED_BODY()

	UBaseComponent* components[MAX_ENTITY_COUNT];

	void AddComponent(UBaseComponent* component, int entityId)
	{
		components[entityId] = component;
	}

	void RemoveComponent(int entityId)
	{
		components[entityId] = nullptr;
	}
};
