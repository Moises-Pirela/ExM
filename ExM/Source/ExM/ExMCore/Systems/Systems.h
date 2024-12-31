#pragma once

#include "ExM/ExMCore/Core/EntityContainer.h"
#include "Systems.generated.h"

UENUM()
enum ESystemTickType : int {
	SYSTEM_TICK,
	SYSTEM_POSTPROCESS,
	SYSTEM_FIXED_TICK,

	SYSTEM_MAX
};

UCLASS(Abstract)
class EXM_API USystemBase : public UObject {
	GENERATED_BODY()

public:
	virtual void Process(EntityContainer* entityContainer, float deltaTime) PURE_VIRTUAL(USystemBase::Process, return;);

	virtual ESystemTickType GetSystemTickType() PURE_VIRTUAL(USystemBase::GetSystemTickType, return ESystemTickType::SYSTEM_TICK;);
};
