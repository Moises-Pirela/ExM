#pragma once


#include "ExM/ExMCore/Core/EntityComponent.h"
#include "ExM/ExMCore/Core/EntityComponentConfig.h"
#include "HealthComponentConfig.generated.h"

UCLASS(EditInlineNew, BlueprintType)
class EXM_API  UHealthComponentConfig : public UEntityComponentConfigBase {
	
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Config")
	float initialMaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Config")
	float initialCurrentHealth;

	virtual FEntityComponent* CreateComponent() override {
		return new FHealthComponent();
	};

	virtual UStruct* GetComponentTypeId() override {
		return FHealthComponent::StaticStruct();
	};
};