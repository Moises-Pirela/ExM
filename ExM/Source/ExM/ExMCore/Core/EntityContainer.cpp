#include "EntityContainer.h"

#include "ComponentArray.h"
#include "Entity.h"

void EntityContainer::CreateEntity(UEntity* entity)
{
	int entityId = -1;
	
	if (recycledEntityId == -1)
	{
		entityId = recycledEntityId;
	}
	else
	{
		entityId = availableEntityId;
		availableEntityId++;
	}

	TArray<UBaseComponent*> _components = entity->GetComponents();
	uint32 componentCount =  _components.Num();
	EComponentTypes* _componentTypes = new EComponentTypes[componentCount];

	for (uint32 i = 0; i < componentCount; i++)
	{
		_componentTypes[i] = _components[i]->GetComponentType();

		componentArrays[_components[i]->GetComponentType()]->AddComponent(_components[i], entityId);
	}

	entity->entityFlags = new FEntityFlags();
	entity->componentSignature = new FComponentFlags (_componentTypes, componentCount);

	entity->entityFlags->AddFlag(ENTITY_STATE_ACTIVE);
	entity->entityFlags->RemoveFlag(ENTITY_STATE_INACTIVE);

	delete _componentTypes;
}

void EntityContainer::RemoveEntity(uint32 entityId)
{
	UEntity* entity = entities[entityId];

	entity->entityFlags->AddFlag(ENTITY_STATE_DEAD);
	
	TArray<UBaseComponent*> _components = entity->GetComponents();
	uint32 componentCount =  _components.Num();

	for (uint32 i = 0; i < componentCount; i++)
	{
		componentArrays[_components[i]->GetComponentType()]->RemoveComponent(entityId);
	}
}
