// © 2024 Necrotek Labs. All rights reserved. ExMORTALIS, including its title, logo, concept, storyline, and associated assets, is a trademark of Necrotek Labs. Unauthorized use, distribution, or reproduction of any part of this game or its materials is strictly prohibited. All other trademarks and trade names are the property of their respective owners. For inquiries, please contact necroteklabs@gmail.com.
#include "ExMHealthComponent.h"
#include "ExMResistancesComponent.h"
#include "ExmStatsComponent.h"
#include "ExM/ExMCore/Utils/DamageCalculators.h"
#include "ExM/ExMCore/Utils/StatHelpers.h"


UExMHealthComponent::UExMHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UExMHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	resistancesComponent = GetOwner()->GetComponentByClass<UExMResistancesComponent>();
	statsComponent = GetOwner()->GetComponentByClass<UExmStatsComponent>();

	maxHealth.SetBaseValue(CalculateMaxHealth(statsComponent->attributes[ATTRIBUTE_STRENGTH].GetValue(), maxHealth.baseVal, 1));
	currentHealth = maxHealth.baseVal;
}

void UExMHealthComponent::TakeDamage(const FDamageData& damageData)
{
	float _finalDamage = damageData.baseDamage;
	EDamageTypes _damageType = damageData.damageType;
	
	float _damageModifier = 1;

	if (resistancesComponent)
	{
		_damageModifier = resistancesComponent->Resistances[_damageType];
	}
	
	_finalDamage = damageCalculators[_damageType](_finalDamage, _damageModifier, 1); //TODO: Apply stacks correctly
	
	currentHealth = FMath::Clamp(currentHealth - _finalDamage, 0, maxHealth.modifiedVal);

	if (currentHealth <= 0)
	{
		if (OnDie.IsBound())
			OnDie.Broadcast();
	}
}
