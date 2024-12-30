#include "DamageSystem.h"

#include "ExM/ExMCore/Core/EntityComponent.h"
#include "ExM/ExMCore/Utils/DamageCalculators.h"

void UDamageSystem::Process(EntityContainer& entityContainer, float deltaTime)
{
	Super::Process(entityContainer, deltaTime);

	for(IPostProcessEvent* _event : entityContainer.postProcessEvents)
	{
		if(DamagePostProcessEvent* _damage = (DamagePostProcessEvent*)_event)
		{
			auto healthComponent = entityContainer.GetComponent<FHealthComponent>(_damage->damageTakerEntityId);

			auto damageComponent = entityContainer.GetComponent<FDamageComponent>(_damage->damageDealerEntityId);

			float totalDamage = damageCalculators[damageComponent->damageType](damageComponent->damage.GetValue(), 0, 1);

			healthComponent->health.modifiedVal -= totalDamage;
		}

		entityContainer.eventPool.Deallocate(_event);
	}
}
