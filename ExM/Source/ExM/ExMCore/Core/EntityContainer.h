#pragma once
#include "ComponentArray.h"
#include "CoreMinimal.h"
#include "CreateEntityEvent.h"
#include "ExM/ExMCore/Utils/Exmortalis.h"
#include "ExM/ExMCore/Components/BaseComponent.h"
#include "ExM/ExMCore/Core/Entity.h"

class UEntityConfig;

static int MAX_COMPONENT_TYPES;

typedef void (*OnKillEntity)(int entityId);

class EntityContainer {
public:
	UEntity*                                               unrealEntities[MAX_ENTITY_COUNT];
	FEntity                                                entities[MAX_ENTITY_COUNT];
	TArray<FComponentArray*>                               componentArrays;
	TArray<CreateEntityEvent>                              createEntityEvents;
	TMap<UStruct*, int>                                    componentTypeIdMap;
	TArray<TFunction<void(UEntityConfig*, int, UEntity*)>> entityCreateObservers;
	TArray<TFunction<void(int)>>                           entityKillObservers;

	EntityContainer(): unrealEntities{}, componentArrays{}, availableEntityId(0), lastRecycledEntityId(-1)
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

	template <typename T>
	void AddComponent(int32 entityID, const T& componentData);
	template <typename T>
	T* GetComponent(int32 entityID);

private :
	int availableEntityId;
	int lastRecycledEntityId;
};
