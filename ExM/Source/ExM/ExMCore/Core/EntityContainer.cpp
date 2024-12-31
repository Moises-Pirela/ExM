#include "EntityContainer.h"

#include "ComponentArray.h"
#include "Entity.h"
#include "EntityComponent.h"
#include "EntityComponentConfig.h"
#include "ExM/ExMCharacter.h"
#include "ExM/ExMCore/Configs/EntityConfig.h"
#include "ExM/ExMCore/Utils/Logger.h"

void EntityContainer::CreateEntity(UEntityConfig* entityConfig, UEntity* startingEntity)
{
	int entityId = -1;

	FEntity entity = FEntity();

	if (lastRecycledEntityId != -1)
	{
		entityId = lastRecycledEntityId;
	}
	else
	{
		entityId = availableEntityId;
		availableEntityId++;
	}

	entity.id = entityId;

	auto _components = entityConfig->componentConfigs;
	int componentCount = _components.Num();

	for (int i = 0; i < componentCount; i++)
	{
		auto component = entityConfig->componentConfigs[i]->CreateComponent();
		UStruct* componentType = entityConfig->componentConfigs[i]->GetComponentTypeId();

		if (!componentTypeIdMap.Contains(componentType))
		{
			auto message = FString::Printf(TEXT("Component type not found: %s %s"), *componentType->GetName(), *entityConfig->componentConfigs[i]->GetName());
			NecroLog(message, ELogLevel::LOG_ERROR);
			
			continue;
		}

		auto message = FString::Printf(TEXT("Component type found: %s %s"), *componentType->GetName(), *entityConfig->componentConfigs[i]->GetName());
		NecroLog(message, ELogLevel::LOG_DEBUG);

		if (componentType == FPlayerTag::StaticStruct())
		{
			PLAYER_ENTITY_ID = entityId;
		}

		if (componentType == FPlayerMovementComponent::StaticStruct())
		{
			((FPlayerMovementComponent*)component)->character = Cast<AExMCharacter>(startingEntity->GetOwner());
		}
		
		int componentTypeId = componentTypeIdMap[componentType];
		componentArrays[componentTypeId]->AddComponent(component, entityId);
		entity.componentSignature.AddFlag(componentTypeId);
	}

	for(auto& _archetype : archetypes)
	{
		if (entity.componentSignature.MatchesSignature(_archetype.Value.signatureHash))
		{
			_archetype.Value.entities.Add(entityId);
		}
	}

	entity.entityFlags.AddFlag(ENTITY_STATE_ACTIVE);
	entity.entityFlags.RemoveFlag(ENTITY_STATE_INACTIVE);
	
	entities[entityId] = entity;

	for (int i = 0; i < entityCreateObservers.Num(); i++)
	{
		entityCreateObservers[i](entityConfig, entityId, startingEntity);
	}
}


void EntityContainer::KillEntity(int entityId)
{
	for (int componentTypeId = 0; componentTypeId < MAX_COMPONENT_TYPES; ++componentTypeId)
	{
		if (entities[entityId].componentSignature.HasFlag(componentTypeId))
		{
			if (componentArrays[componentTypeId])
			{
				componentArrays[componentTypeId]->RemoveComponent(entityId);
			}
		}
	}
	
	entities[entityId] = FEntity::Empty();
	lastRecycledEntityId = entityId;
	
	for (int i = 0; i < entityKillObservers.Num(); i++)
	{
		entityKillObservers[i](entityId);
	}
	
}