#pragma once

inline float CalculateThrowStrength(int strengthStat, float throwableMass, float modifiers)
{
	float baseStrength = sqrt(strengthStat * 100.0f / throwableMass);

	float finalThrowStrength = baseStrength * modifiers;

	return finalThrowStrength;
}

inline float CalculateMaxHealth(int strengthStat, int vitalityStat, float baseMaxHealth, float modifiers)
{
	float healthMultiplier = 1.0f + (vitalityStat * 0.5f + strengthStat * 0.25f) / 100.0f;

	float maxHealth = baseMaxHealth * healthMultiplier;

	maxHealth *= modifiers;

	return maxHealth;
}

inline float CalculateMovementSpeed(int dexterity, float baseWalkSpeed, float modifiers)
{
	float speedMultiplier = 1.0f + dexterity * 0.01f;

	float movementSpeed = baseWalkSpeed * speedMultiplier;

	movementSpeed *= modifiers;

	return movementSpeed;
}

inline float CalculateJumpHeight(int strength, int dexterity, float baseJumpHeight, float modifiers)
{
	float jumpMultiplier = 1.0f + (strength * 0.02f) + (dexterity * 0.01f);

	float jumpHeight = baseJumpHeight * jumpMultiplier;

	jumpHeight *= modifiers;

	return jumpHeight;
}
