// © 2024 Necrotek Labs. All rights reserved. ExMORTALIS, including its title, logo, concept, storyline, and associated assets, is a trademark of Necrotek Labs. Unauthorized use, distribution, or reproduction of any part of this game or its materials is strictly prohibited. All other trademarks and trade names are the property of their respective owners. For inquiries, please contact necroteklabs@gmail.com.


#include "CreateEntitySystem.h"

void UCreateEntitySystem::Process(EntityContainer* entityContainer, float deltaTime)
{
	for(IPostProcessEvent* _event : entityContainer->postProcessEvents)
	{
		if(CreateEntityEvent* _createEntityEvent = (CreateEntityEvent*)_event)
		{
			entityContainer->CreateEntity(_createEntityEvent->pConfig, _createEntityEvent->pUnrealEntity);
			entityContainer->eventPool.Deallocate(_event);
		}
	}
}

ESystemTickType UCreateEntitySystem::GetSystemTickType()
{
	return ESystemTickType::SYSTEM_POSTPROCESS;
}
