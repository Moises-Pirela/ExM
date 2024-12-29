#pragma once
#include "EntityComponent.h"
#include "EntityComponentConfig.generated.h"

UCLASS(EditInlineNew, BlueprintType)
class EXM_API UEntityComponentConfigBase : public UObject {

	GENERATED_BODY()

public:
	UEntityComponentConfigBase(){};
	virtual FEntityComponent* CreateComponent() PURE_VIRTUAL(FEntityComponentConfigBase::CreateComponent, return nullptr;);
	virtual UStruct* GetComponentTypeId() PURE_VIRTUAL(FEntityComponentConfigBase::GetComponentTypeId, return FEntityComponent::StaticStruct(););
};