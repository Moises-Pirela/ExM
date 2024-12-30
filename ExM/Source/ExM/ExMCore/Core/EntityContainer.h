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
	Pool<IPostProcessEvent>                eventPool;
	TMap<UStruct*, int>                                    componentTypeIdMap;
	TArray<TFunction<void(UEntityConfig*, int, UEntity*)>> entityCreateObservers;
	TArray<TFunction<void(int)>>                           entityKillObservers;

private:
	TArray<IPostProcessEvent*> postProcessEvents;

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

	void ProcessEvents();

	void AddEvent(IPostProcessEvent* event)
	{
		postProcessEvents.Add(event);
	}

	template <typename T>
	void AddComponent(int32 entityID, const T& componentData);
	template <typename T>
	T* GetComponent(int32 entityID);

private :
	int availableEntityId;
	int lastRecycledEntityId;
};
