#pragma once

#include "ExM/ExMCore/Core/EntityComponent.h"
#include "ExM/ExMCore/Core/EntityComponentConfig.h"
#include "StatComponentConfig.generated.h"

UCLASS(EditInlineNew, BlueprintType)
class EXM_API UStatComponentConfig : public UEntityComponentConfigBase {
	
	GENERATED_BODY()

public:

UPROPERTY(EditAnywhere, BlueprintReadOnly)
float strength;

UPROPERTY(EditAnywhere, BlueprintReadOnly)
float dexterity;

UPROPERTY(EditAnywhere, BlueprintReadOnly)
float intelligence;

	virtual FEntityComponent* CreateComponent() override {
		return new FStatComponent();
	};

	virtual UStruct* GetComponentTypeId() override {
		return FStatComponent::StaticStruct();
	};
};