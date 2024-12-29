#include "Entity.h"
#include "CreateEntityEvent.h"
#include "EntitySubsystem.h"

void UEntity::SetupEntity()
{
	auto subsystem = GetWorld()->GetSubsystem<UEntitySubsystem>();
	CreateEntityEvent _createEntityEvent;
	_createEntityEvent.pConfig = entityConfig;
	_createEntityEvent.pUnrealEntity = this;
	subsystem->entityContainer->createEntityEvents.Add(_createEntityEvent);
}

void UEntity::BeginPlay()
{
	Super::BeginPlay();

	if (bIsStartingEntity)
		SetupEntity();
}

void UEntity::DestroyComponent(bool bPromoteChildren)
{
	Super::DestroyComponent(bPromoteChildren);
}
