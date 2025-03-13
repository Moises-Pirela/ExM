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

	template <typename T>
	T* GetComponentConfig() const
	{
		static_assert(TIsDerivedFrom<T, UEntityComponentConfigBase>::Value,
		              "T must derive from UEntityComponentConfigBase");

		for (UEntityComponentConfigBase* Config : componentConfigs)
		{
			if (T* TypedConfig = Cast<T>(Config))
			{
				return TypedConfig;
			}
		}

		return nullptr;
	}
};


