#pragma once

class UEntityConfig;
class UEntity;

struct CreateEntityEvent
{
	UEntityConfig *pConfig;
	UEntity* pUnrealEntity;
	
	CreateEntityEvent(): pConfig(nullptr)
	{
	};
};
