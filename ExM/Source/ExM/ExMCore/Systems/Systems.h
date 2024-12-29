#pragma once
#include "AITestsCommon.h"
#include "ExM/ExMCore/Components/BuffableComponent.h"
#include "ExM/ExMCore/Core/Entity.h"


class UEntity;
struct FComponentArray;

typedef void (*EntitySystem)(UWorld* world, UEntity *entities[], TArray<FComponentArray*> componentArray, float deltaTime);

enum ESystemType
{
	SYSTEM_BUFF,
	SYSTEM_DAMAGE,

	SYSTEM_MAX
};

inline void BuffSystem(UWorld* world, UEntity *entities[], TArray<FComponentArray*> componentArray, float deltaTime)
{
}

inline void DamageSystem(UWorld* world, UEntity *entities[], TArray<FComponentArray*> componentArray, float deltaTime)
{
}

inline EntitySystem systems[SYSTEM_MAX] =
{
	{BuffSystem},
	{DamageSystem}
};