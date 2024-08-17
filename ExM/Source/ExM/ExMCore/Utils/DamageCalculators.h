#pragma once
#include <map>

#include "Exmortalis.h"

UENUM(BlueprintType)
enum EDamageTypes : int
{
	DAMAGE_TYPE_KINETIC = 0,
	DAMAGE_TYPE_BLUNT,
	DAMAGE_TYPE_SLASH,
	DAMAGE_TYPE_NECROTIC,
	DAMAGE_TYPE_FALL,
	DAMAGE_TYPE_MAX,
};

typedef float (*DamageCalculator)(float damage, float resistance, int stacks);

constexpr float FALL_DAMAGE_THRESHOLD = 5 * UE_UNITS_TO_METERS; 
constexpr float FALL_DAMAGE_FACTOR = 5; 

inline float CalculateKineticDamage(float baseDamage, float resistance, int stacks)
{
	return baseDamage * (1.0f - resistance);
};

inline float CalculateBluntDamage(float baseDamage, float resistance, int stacks)
{
	return baseDamage * (1.0f - resistance);
};

inline float CalculateSlashDamage(float baseDamage, float resistance, int stacks)
{
	return baseDamage * (1.0f - resistance);
};

inline float CalculateNecroticDamage(float baseDamage, float resistance, int stacks)
{
	return baseDamage * (1.0f - resistance);
};

inline float CalculateFallDamage(float fallHeight, float resistance, int stacks)
{
	if (fallHeight <= FALL_DAMAGE_THRESHOLD) {
		return 0.0f;
	}
	
	float _heightAboveThreshold = fallHeight - FALL_DAMAGE_THRESHOLD;
	
	float _baseDamage = FALL_DAMAGE_FACTOR * FMath::Pow(_heightAboveThreshold, 2);
	
	return _baseDamage * (1.0f - resistance);
};

inline DamageCalculator damageCalculators[DAMAGE_TYPE_MAX] =
{
	{CalculateKineticDamage},
	{CalculateBluntDamage},
	{CalculateSlashDamage},
	{CalculateNecroticDamage},
	{CalculateFallDamage},
};
