#include "ExmStatsComponent.h"

UExmStatsComponent::UExmStatsComponent()
{
}

void UExmStatsComponent::SetDerivedStats()
{
	float moveSpeed = CalculateMovementSpeed(attributes[ATTRIBUTE_DEXTERITY].GetValue(), 475, 1);
	derivedStats[DERIVED_STAT_MOVEMENT_SPEED].SetBaseValue(moveSpeed);
	derivedStats[DERIVED_STAT_SPRINT_SPEED].SetBaseValue(moveSpeed * 2);
}

void UExmStatsComponent::Init()
{
	for (int i = 0; i < ATTRIBUTE_MAX; i++)
	{
		int baseValue = attributes[(EAttributeTypes)i].baseVal;
		attributes[(EAttributeTypes)i].SetBaseValue(baseValue);
	}

	SetDerivedStats();
}
