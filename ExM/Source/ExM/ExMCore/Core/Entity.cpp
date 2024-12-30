#include "Entity.h"
#include "EntitySubsystem.h"

void UEntity::SetupEntity()
{
	auto subsystem = GetWorld()->GetSubsystem<UEntitySubsystem>();
	CreateEntityEvent* _createEntityEvent = (CreateEntityEvent*)subsystem->entityContainer->eventPool.Allocate();
	_createEntityEvent->pConfig = entityConfig;
	_createEntityEvent->pUnrealEntity = this;
	subsystem->SendPostprocessEvent(_createEntityEvent);
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
