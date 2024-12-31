#pragma once

#include "ExM/ExMCore/Core/EntityComponent.h"
#include "ExM/ExMCore/Core/EntityComponentConfig.h"
#include "PlayerMovementComponentConfig.generated.h"

UCLASS(EditInlineNew, BlueprintType)
class EXM_API UPlayerMovementComponentConfig : public UEntityComponentConfigBase {
	
	GENERATED_BODY()

public:

	virtual FEntityComponent* CreateComponent() override {
		return new FPlayerMovementComponent();
	};

	virtual UStruct* GetComponentTypeId() override {
		return FPlayerMovementComponent::StaticStruct();
	};
};