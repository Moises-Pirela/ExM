// © 2024 Necrotek Labs. All rights reserved. ExMORTALIS, including its title, logo, concept, storyline, and associated assets, is a trademark of Necrotek Labs. Unauthorized use, distribution, or reproduction of any part of this game or its materials is strictly prohibited. All other trademarks and trade names are the property of their respective owners. For inquiries, please contact necroteklabs@gmail.com.


#include "EntitySubsystem.h"

#include "EntityComponent.h"
#include "EntityContainer.h"
#include "ExM/ExMCore/Configs/EntityConfig.h"
#include "ExM/ExMCore/Systems/Systems.h"
#include "ExM/ExMCore/Utils/Logger.h"

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

	// for(auto systemRun : systems)
	// {
	// 	systemRun(GetWorld(), entityContainer, deltaTime);
	// }

	entityContainer->postProcessEvents.Empty();
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

			CreateEntityEvent* _createEntityEvent = (CreateEntityEvent*)entityContainer->eventPool.Allocate();

			_createEntityEvent->pConfig = unrealEntity->entityConfig;
			_createEntityEvent->pUnrealEntity = unrealEntity;

			SendPostprocessEvent(_createEntityEvent);
		}
	} 
}

bool UEntitySubsystem::GetComponentByUSTRUCT(FName structName, int entityId, FEntityComponent& component) {
	UStruct* type = FindObject<UStruct>(ANY_PACKAGE, *structName.ToString());

	if (!type)
	{
		FString mess = FString::Printf(TEXT("Struct type not found for name: %s"), *structName.ToString());
		NecroLog(mess, LOG_DEBUG);
	} else
	{
		FString mess = FString::Printf(TEXT("Struct type found for name: %s"), *structName.ToString());
		NecroLog(mess, LOG_DEBUG);
	}

	if (!entityContainer->componentTypeIdMap.Contains(type)) return false;
	
	int componentTypeId = entityContainer->componentTypeIdMap[type];

	if (entityContainer->componentArrays[componentTypeId]->components[entityId] == nullptr) return false;

	component = *entityContainer->componentArrays[componentTypeId]->components[entityId];
	
	return true;
}

void UEntitySubsystem::OnCreateEntity(UEntityConfig* entityConfig, int entityId, UEntity* startingEntity) {
	if(startingEntity)
	{
		entityContainer->unrealEntities[entityId] = startingEntity;
	}
}

void UEntitySubsystem::SendPostprocessEvent(IPostProcessEvent* postProcessEvent) {
	entityContainer->AddEvent(postProcessEvent);
}

void UEntitySubsystem::OnKillEntity(int entityId) {
	GetWorld()->DestroyActor(entityContainer->unrealEntities[entityId]->GetOwner());

	entityContainer->unrealEntities[entityId] = nullptr;
}

TStatId UEntitySubsystem::GetStatId() const {
	return TStatId();
}
