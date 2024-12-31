#pragma once
#include "Entity.h"

enum EArchetype {
	ARCHETYPE_PLAYER,
	ARCHETYPE_WEAPON,
	ARCHETYPE_ENEMY
};

struct Archetype {
	FComponentFlags signatureHash;
	TArray<int>     entities;
};