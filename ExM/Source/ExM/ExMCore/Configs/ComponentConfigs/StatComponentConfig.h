#pragma once

#include "ExM/ExMCore/Core/EntityComponent.h"
#include "ExM/ExMCore/Core/EntityComponentConfig.h"
#include "StatComponentConfig.generated.h"

UCLASS(EditInlineNew, BlueprintType)
class EXM_API UAttributesComponentConfig : public UEntityComponentConfigBase {
	
	GENERATED_BODY()

public:

UPROPERTY(EditAnywhere, BlueprintReadOnly)
int strength;

UPROPERTY(EditAnywhere, BlueprintReadOnly)
int dexterity;

UPROPERTY(EditAnywhere, BlueprintReadOnly)
int intelligence;

	virtual FEntityComponent* CreateComponent() override {
		return new FAttributesComponent();
	};

	virtual UStruct* GetComponentTypeId() override {
		return FAttributesComponent::StaticStruct();
	};
};