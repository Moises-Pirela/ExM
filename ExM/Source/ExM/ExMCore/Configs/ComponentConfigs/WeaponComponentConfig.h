#pragma once

#include "ExM/ExMCore/Core/EntityComponent.h"
#include "ExM/ExMCore/Core/EntityComponentConfig.h"
#include "WeaponComponentConfig.generated.h"

UCLASS(EditInlineNew, BlueprintType)
class EXM_API UWeaponComponentConfig : public UEntityComponentConfigBase {
	
	GENERATED_BODY()

public:

	virtual FEntityComponent* CreateComponent() override {
		return new FWeaponComponent();
	};

	virtual UStruct* GetComponentTypeId() override {
		return FWeaponComponent::StaticStruct();
	};
};