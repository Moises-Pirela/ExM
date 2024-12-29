#pragma once

#include "CoreMinimal.h"
#include "ExM/ExMCore/Configs/ComponentConfigs/HealthComponentConfig.h"
#include "EntityConfig.generated.h"

class UHealthComponentConfig;
class UEntityComponentConfigBase;

UCLASS(EditInlineNew, BlueprintType)
class EXM_API UEntityConfig : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId(TEXT("EntityConfig"), GetFName());
	}
	
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Components")
	TArray<UEntityComponentConfigBase*> componentConfigs;
};


