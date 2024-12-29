#pragma once
#include "Exmortalis.h"

inline float fastSqrt(float number)
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;
	i  = 0x5f3759df - ( i >> 1 );
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );

	return y;
}

constexpr float CalculateThrowStrength(int strengthStat, float throwableMass, float modifiers)
{
	float baseStrength = (strengthStat * strengthStat) * 1000.0f / (throwableMass + 1.0f);

	float finalThrowStrength = baseStrength * modifiers;

	return finalThrowStrength;
}

constexpr float CalculateMaxHealth(int strengthStat, float baseMaxHealth, float modifiers)
{
	float healthMultiplier = 1.0f + (strengthStat * 0.5f + strengthStat * 0.25f) / 100.0f;
	float maxHealth = baseMaxHealth * healthMultiplier;
	maxHealth *= modifiers;
	return maxHealth;
}

constexpr float CalculateMovementSpeed(int dexterity, float baseWalkSpeed, float modifiers)
{
	float speedMultiplier = 1.0f + dexterity * 0.01f;
	float movementSpeed = baseWalkSpeed * speedMultiplier;
	movementSpeed *= modifiers;
	return movementSpeed;
}

constexpr float CalculateReloadSpeed(int dexterity, int intelligence, float modifiers)
{
	constexpr float dexterityWeight = 0.7f;
	constexpr float intelligenceWeight = 0.3f;
	constexpr float maxReloadSpeed = 2.0f;

	float baseReloadSpeed = (dexterity * dexterityWeight + intelligence * intelligenceWeight) / MAX_ATTRIBUTE_VALUE;

	float finalReloadSpeed = baseReloadSpeed * modifiers;

	return FMath::Clamp(finalReloadSpeed, 0.0f, maxReloadSpeed);
}

constexpr float CalculateJumpHeight(int strength, int dexterity, float baseJumpHeight, float modifiers)
{
	float jumpMultiplier = 1.0f + (strength * 0.02f) + (dexterity * 0.01f);
	float jumpHeight = baseJumpHeight * jumpMultiplier;
	jumpHeight *= modifiers;
	return jumpHeight;
}
