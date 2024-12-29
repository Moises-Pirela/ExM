#pragma once

#include "ExM/ExMCore/Core/EntityComponent.h"
#include "ExM/ExMCore/Core/EntityComponentConfig.h"
#include "MovementStateComponentConfig.generated.h"

UCLASS(EditInlineNew, BlueprintType)
class EXM_API UMovementStateComponentConfig : public UEntityComponentConfigBase {
	
	GENERATED_BODY()

public:

	virtual FEntityComponent* CreateComponent() override {
		return new FMovementStateComponent();
	};

	virtual UStruct* GetComponentTypeId() override {
		return FMovementStateComponent::StaticStruct();
	};
};