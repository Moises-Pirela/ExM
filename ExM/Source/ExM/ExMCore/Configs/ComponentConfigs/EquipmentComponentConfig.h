#pragma once

#include "ExM/ExMCore/Core/EntityComponent.h"
#include "ExM/ExMCore/Core/EntityComponentConfig.h"
#include "EquipmentComponentConfig.generated.h"

class UEntityConfig;

UCLASS(EditInlineNew, BlueprintType)
class EXM_API  UEquipmentComponentConfig : public UEntityComponentConfigBase {
	
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment Config")
	UEntityConfig* startingWeaponEntityConfig;

	virtual FEntityComponent* CreateComponent() override {
		return new FEquipmentComponent();
	};

	virtual UStruct* GetComponentTypeId() override {
		return FEquipmentComponent::StaticStruct();
	};
};