#pragma once
#include "ExM/ExMPlayerController.h"

class UEntityConfig;
class UEntity;

struct IPostProcessEvent {
};

struct InputPostProcessEvent : public IPostProcessEvent {
	FInputData inputData;
};

struct DamagePostProcessEvent : public IPostProcessEvent {
	int damageDealerEntityId;
	int damageTakerEntityId;
};

struct CreateEntityEvent : public IPostProcessEvent {
	
	UEntityConfig *pConfig;
	UEntity* pUnrealEntity;
};
