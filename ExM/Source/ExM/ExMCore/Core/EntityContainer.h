#pragma once
#include "ComponentArray.h"
#include "CoreMinimal.h"
#include "IPostProcessEvent.h"
#include "ExM/ExMCore/Utils/Exmortalis.h"
#include "ExM/ExMCore/Core/Entity.h"
#include "..\Utils\Pool.h"

class UEntityConfig;

static int MAX_COMPONENT_TYPES;

typedef void (*OnKillEntity)(int entityId);

class EntityContainer {
public:
	UEntity*                                               unrealEntities[MAX_ENTITY_COUNT];
	FEntity                                                entities[MAX_ENTITY_COUNT];
	TArray<FComponentArray*>                               componentArrays;
	TArray<IPostProcessEvent*>                             postProcessEvents;
	Pool<IPostProcessEvent>                                eventPool;
	TMap<UStruct*, int>                                    componentTypeIdMap;
	TArray<TFunction<void(UEntityConfig*, int, UEntity*)>> entityCreateObservers;
	TArray<TFunction<void(int)>>                           entityKillObservers;

public:
	EntityContainer() : unrealEntities{}, componentArrays{}, eventPool(10), availableEntityId(0), lastRecycledEntityId(-1)
	{
		for(int i = 0; i < MAX_ENTITY_COUNT; i++)
		{
			entities[i] = FEntity();
		}

		for(int i = 0; i < MAX_COMPONENT_TYPES; i++)
		{
			componentArrays.Add(new FComponentArray());
		}
	}

	void CreateEntity(UEntityConfig* entityConfig, UEntity* startingEntity);

	void KillEntity(int entityId);

	void AddEvent(IPostProcessEvent* event)
	{
		postProcessEvents.Add(event);
	}

	template <typename T>
	void AddComponent(int32 entityID, const T& componentData)
	{
		UStruct* _componentClass = T::StaticStruct();
		int32 _componentTypeId = *componentTypeIdMap.Find(_componentClass);

		componentArrays[_componentTypeId]->components[entityID] = componentData;
	}

	template <typename T>
	T* GetComponent(int32 entityID)
	{
		UStruct* _componentClass = T::StaticStruct();
		int32 _componentTypeId = *componentTypeIdMap.Find(_componentClass);
	
		return static_cast<T*>(componentArrays[_componentTypeId]->components[entityID]);
	}

private :
	int availableEntityId;
	int lastRecycledEntityId;
};
