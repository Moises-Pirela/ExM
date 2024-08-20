#pragma once
#include "ComponentArray.h"
#include "ExM/ExMCore/Components/BaseComponent.h"


struct FComponentArray;
class UEntity;

constexpr uint32 MAX_ENTITY_COUNT = 100;

class EntityContainer
{
public:

	UEntity *entities[MAX_ENTITY_COUNT];
	FComponentArray *componentArrays[COMPONENT_MAX];
	
	EntityContainer(): entities{}, componentArrays{}, availableEntityId(0), recycledEntityId(-1)
	{
		for (int i =0 ; i < COMPONENT_MAX; i++)
		{
			componentArrays[i] = new FComponentArray{};
		}
	}

	void CreateEntity(UEntity *entity);

	void RemoveEntity(uint32 entityId);

	static EntityContainer& instance()
	{
		static EntityContainer *instance = new EntityContainer();
		return *instance;
	}
private :
	uint32 availableEntityId;
	uint32 recycledEntityId;
};
