#pragma once

#include "ExM/ExMCore/Core/EntityComponent.h"
#include "ExM/ExMCore/Core/EntityComponentConfig.h"
#include "InventoryComponentConfig.generated.h"

UCLASS(EditInlineNew, BlueprintType)
class EXM_API  UInventoryComponentConfig : public UEntityComponentConfigBase {
	
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Config")
	int initialInventorySize;

	virtual FEntityComponent* CreateComponent() override {
		return new FInventoryComponent();
	};

	virtual UStruct* GetComponentTypeId() override {
		return FInventoryComponent::StaticStruct();
	};
};