#pragma once
#include "EntityComponent.h"

class UEntityConfig;
class UEntity;

struct IPostProcessEvent {
};

struct InputPostProcessEvent : public IPostProcessEvent {
	FPlayerInputData inputData;
};

struct DamagePostProcessEvent : public IPostProcessEvent {
	int damageDealerEntityId;
	int damageTakerEntityId;
};

struct CreateEntityEvent : public IPostProcessEvent {
	
	UEntityConfig *pConfig;
	UEntity* pUnrealEntity;
};
