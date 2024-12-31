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
			}
		}
	}

	MAX_COMPONENT_TYPES = _idCounter + 1;

	entityContainer = new EntityContainer(componentTypeIdMap);

	entityContainer->entityCreateObservers.Add([this](UEntityConfig* entityConfig, int entityId, UEntity* startingEntity)
	{
		OnCreateEntity(entityConfig, entityId, startingEntity);
	});

	entityContainer->entityKillObservers.Add([this](int entityId)
	{
		OnKillEntity(entityId);
	});

	//LOAD SYSTEMS
	for(TObjectIterator<UClass> It; It; ++It)
	{
		UClass* _class = *It;

		if(_class->IsChildOf(USystemBase::StaticClass()))
		{
			if(_class->HasAnyClassFlags(CLASS_Abstract))
			{
				auto mess = FString::Printf(TEXT("Skip base system %s"), *_class->GetName());
				NecroLog(mess, ELogLevel::LOG_WARNING);
				continue;
			}

			USystemBase* systemInstance = NewObject<USystemBase>(this, _class);
			ESystemTickType tickType = systemInstance->GetSystemTickType();
			auto            message = FString::Printf(TEXT("Load system %s"), *_class->GetName());
			NecroLog(message, ELogLevel::LOG_WARNING);

			systems.FindOrAdd(tickType).Add(TStrongObjectPtr<USystemBase>(systemInstance));
		}
	}
}

void UEntitySubsystem::Deinitialize()
{
	Super::Deinitialize();

	if(entityContainer)
	{
		delete entityContainer;
		entityContainer = nullptr;
	}

	systems.Empty();
}

void UEntitySubsystem::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	// Process SYSTEM_TICK systems
	const auto& systemTickArray = systems[ESystemTickType::SYSTEM_TICK];
	for(int32 i = 0; i < systemTickArray.Num(); ++i)
	{
		auto systemRun = systemTickArray[i];
		if(systemRun)
		{
			systemRun->Process(entityContainer, deltaTime);
		}
	}

	// Process SYSTEM_POSTPROCESS systems
	const auto& systemPostProcessArray = systems[ESystemTickType::SYSTEM_POSTPROCESS];
	for(int32 i = 0; i < systemPostProcessArray.Num(); ++i)
	{
		auto systemRun = systemPostProcessArray[i];
		if(systemRun)
		{
			systemRun->Process(entityContainer, deltaTime);
		}
	}

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
			AActor*  spawnedActor = world->SpawnActor<AActor>(entityActor->GetClass(), FTransform(), spawnParams);
			UEntity* unrealEntity = spawnedActor->GetComponentByClass<UEntity>();

			CreateEntityEvent* _createEntityEvent = (CreateEntityEvent*)entityContainer->eventPool.Allocate();

			_createEntityEvent->pConfig = unrealEntity->entityConfig;
			_createEntityEvent->pUnrealEntity = unrealEntity;

			SendPostprocessEvent(_createEntityEvent);
		}
	}
}

bool UEntitySubsystem::GetComponentByUSTRUCT(FName structName, int entityId, FEntityComponent& component)
{
	UStruct* type = FindObject<UStruct>(ANY_PACKAGE, *structName.ToString());

	if(!type)
	{
		FString mess = FString::Printf(TEXT("Struct type not found for name: %s"), *structName.ToString());
		NecroLog(mess, LOG_DEBUG);
	} else
	{
		FString mess = FString::Printf(TEXT("Struct type found for name: %s"), *structName.ToString());
		NecroLog(mess, LOG_DEBUG);
	}

	if(!entityContainer->componentTypeIdMap.Contains(type)) return false;

	int componentTypeId = entityContainer->componentTypeIdMap[type];

	if(entityContainer->componentArrays[componentTypeId]->components[entityId] == nullptr) return false;

	component = *entityContainer->componentArrays[componentTypeId]->components[entityId];

	return true;
}

void UEntitySubsystem::OnCreateEntity(UEntityConfig* entityConfig, int entityId, UEntity* startingEntity)
{
	if(startingEntity)
	{
		entityContainer->unrealEntities[entityId] = startingEntity;
	}
}

void UEntitySubsystem::SendPostprocessEvent(IPostProcessEvent* postProcessEvent)
{
	entityContainer->AddEvent(postProcessEvent);
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
