// © 2024 Necrotek Labs. All rights reserved. ExMORTALIS, including its title, logo, concept, storyline, and associated assets, is a trademark of Necrotek Labs. Unauthorized use, distribution, or reproduction of any part of this game or its materials is strictly prohibited. All other trademarks and trade names are the property of their respective owners. For inquiries, please contact necroteklabs@gmail.com.


#include "EntitySubsystem.h"

#include "EntityComponent.h"
#include "EntityContainer.h"
#include "ExM/ExMCore/Configs/EntityConfig.h"
#include "ExM/ExMCore/Systems/Systems.h"

void UEntitySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	int32 _idCounter = 0;

	TMap<UStruct*, int> componentTypeIdMap;

	for(TObjectIterator<UStruct> It; It; ++It)
	{
		UStruct* _struct = *It;

		if(_struct->IsChildOf(FEntityComponent::StaticStruct()) && _struct != FEntityComponent::StaticStruct())
		{
			if(!componentTypeIdMap.Contains(_struct))
			{
				componentTypeIdMap.Add(_struct, _idCounter++);
				UE_LOG(LogTemp, Log, TEXT("Registered Component: %s with ID: %d"), *_struct->GetName(), _idCounter - 1);
			}
		}
	}

	MAX_COMPONENT_TYPES = _idCounter + 1;

	entityContainer = new EntityContainer();
	entityContainer->componentTypeIdMap = componentTypeIdMap;

	entityContainer->entityCreateObservers.Add([this](UEntityConfig* entityConfig, int entityId, UEntity* startingEntity)
	{
		OnCreateEntity(entityConfig, entityId, startingEntity);
	});

	entityContainer->entityKillObservers.Add([this](int entityId)
	{
		OnKillEntity(entityId);
	});
}

void UEntitySubsystem::Deinitialize()
{
	Super::Deinitialize();

	delete entityContainer;
}

void UEntitySubsystem::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	for(auto systemRun : systems)
	{
		systemRun(GetWorld(), entityContainer->unrealEntities, entityContainer->componentArrays, deltaTime);
	}
}

void UEntitySubsystem::SpawnUnrealEntity(TSoftClassPtr<AActor> entityActor)
{
	if(entityActor)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = nullptr;
		spawnParams.Instigator = nullptr;

		UWorld* world = GetWorld();
		if(world)
		{
			AActor* spawnedActor = world->SpawnActor<AActor>(entityActor->GetClass(), FTransform(), spawnParams);
			UEntity* unrealEntity = spawnedActor->GetComponentByClass<UEntity>();

			CreateEntityEvent _createEntityEvent;

			_createEntityEvent.pConfig = unrealEntity->entityConfig;
			_createEntityEvent.pUnrealEntity = unrealEntity;

			SendCreateEntityEvent(_createEntityEvent);
		}
	} 
}

void UEntitySubsystem::OnCreateEntity(UEntityConfig* entityConfig, int entityId, UEntity* startingEntity)
{
	if(startingEntity)
	{
		entityContainer->unrealEntities[entityId] = startingEntity;
	}
}

void UEntitySubsystem::SendCreateEntityEvent(CreateEntityEvent createEntityEvent)
{
	entityContainer->createEntityEvents.Add(createEntityEvent);
}


void UEntitySubsystem::OnKillEntity(int entityId)
{
	GetWorld()->DestroyActor(entityContainer->unrealEntities[entityId]->GetOwner());

	entityContainer->unrealEntities[entityId] = nullptr;
}

TStatId UEntitySubsystem::GetStatId() const
{
	return TStatId();
}
