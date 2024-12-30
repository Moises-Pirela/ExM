#pragma once
#include "ExM/ExMCore/Core/EntityContainer.h"
#include "Systems.generated.h"

enum ESystemTickType {
	SYSTEM_TICK,
	SYSTEM_POSTPROCESS,
	SYSTEM_FIXED_TICK
};

UCLASS()
class USystemBase : public UObject {

	GENERATED_BODY()
	
public:
	virtual void Process(EntityContainer& entityContainer, float deltaTime) PURE_VIRTUAL();
	virtual ESystemTickType GetSystemTickType() PURE_VIRTUAL(USystemBase::GetSystemTickType, return SYSTEM_TICK;)
};