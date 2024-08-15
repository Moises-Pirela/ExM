#pragma once
#include "ExM/ExMCore/Components/BaseComponent.h"
#include "ExM/ExMCore/Utils/Exmortalis.h"

#include "ComponentArray.generated.h"

class UBaseComponent;

USTRUCT(BlueprintType)
struct FComponentArray
{
	GENERATED_BODY()

	UBaseComponent* components[MAX_ENTITIES];

	void AddComponent(UBaseComponent* component, int entityId)
	{
		components[entityId] = component;
	}

	void RemoveComponent(int entityId)
	{
		components[entityId] = nullptr;
	}
};
