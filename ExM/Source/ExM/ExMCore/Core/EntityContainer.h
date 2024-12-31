#pragma once
#include "ComponentArray.h"
#include "CoreMinimal.h"
#include "Archetypes.h"
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
	TMap<EArchetype, Archetype>                            archetypes;
	inline static int                                      PLAYER_ENTITY_ID = -1;

public:
	EntityContainer(const TMap<UStruct*, int>& componentTypeMap) : unrealEntities{}, componentArrays{}, eventPool(10), availableEntityId(0), lastRecycledEntityId(-1)
	{
		componentTypeIdMap = componentTypeMap;
		
		for(int i = 0; i < MAX_ENTITY_COUNT; i++)
		{
			entities[i] = FEntity();
		}

		for(int i = 0; i < MAX_COMPONENT_TYPES; i++)
		{
			componentArrays.Add(new FComponentArray());
		}

		Archetype playerArchetype = Archetype();
		playerArchetype.signatureHash.AddFlag(componentTypeIdMap[FPlayerTag::StaticStruct()]);

		Archetype weaponArchetype = Archetype();
		weaponArchetype.signatureHash.AddFlag(componentTypeIdMap[FWeaponComponent::StaticStruct()]);

		Archetype enemyArchetype = Archetype();
		enemyArchetype.signatureHash.AddFlag(componentTypeIdMap[FAIComponent::StaticStruct()]);

		archetypes.Add(ARCHETYPE_PLAYER, playerArchetype);
		archetypes.Add(ARCHETYPE_WEAPON, weaponArchetype);
		archetypes.Add(ARCHETYPE_ENEMY, enemyArchetype);

		PLAYER_ENTITY_ID = -1;
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
		int32    _componentTypeId = *componentTypeIdMap.Find(_componentClass);

		componentArrays[_componentTypeId]->components[entityID] = componentData;
	}

	template <typename T>
	T* GetComponent(int32 entityID)
	{
		UStruct* _componentClass = T::StaticStruct();
		int32    _componentTypeId = *componentTypeIdMap.Find(_componentClass);

		return static_cast<T*>(componentArrays[_componentTypeId]->components[entityID]);
	}

	FEntity& GetPlayerEntity()
	{
		return entities[PLAYER_ENTITY_ID];
	}

private :
	int availableEntityId;
	int lastRecycledEntityId;
};
