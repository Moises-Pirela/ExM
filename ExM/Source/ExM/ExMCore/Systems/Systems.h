#pragma once
#include "AITestsCommon.h"
#include "ExM/ExMCore/Components/BuffableComponent.h"
#include "ExM/ExMCore/Core/Entity.h"
#include "ExM/ExMCore/Core/IPostProcessEvent.h"


class UEntity;
struct FComponentArray;

typedef void (*EntitySystem)(UWorld* world, EntityContainer* entityContainer, float deltaTime);

typedef void (*PostprocessSystem)(UWorld* world, EntityContainer* entityContainer, float deltaTime, TArray<IPostProcessEvent> events);

enum ESystemType
{
	SYSTEM_BUFF,
	SYSTEM_DAMAGE,

	SYSTEM_MAX
};

enum EPostprocessSystemType
{
	POST_SYSTEM_DAMAGE,

	POST_SYSTEM_MAX
};

inline void BuffSystem(UWorld* world, EntityContainer* entityContainer, float deltaTime)
{
}

inline void DamageSystem(UWorld* world, EntityContainer* entityContainer, float deltaTime, TArray<IPostProcessEvent>)
{
}

inline EntitySystem systems[SYSTEM_MAX] =
{
	{BuffSystem},
};

inline PostprocessSystem postprocessSystems[POST_SYSTEM_MAX]
{
	{DamageSystem}
};