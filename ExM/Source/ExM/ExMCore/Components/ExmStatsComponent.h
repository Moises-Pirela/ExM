#pragma once


#include "CoreMinimal.h"
#include "BaseComponent.h"
#include "ExmStatsComponent.generated.h"

UENUM(BlueprintType)
enum EStatTypes
{
	STAT_DEXTERITY			UMETA(DisplayName = "Dexterity"),
	STAT_RESOLVE			UMETA(DisplayName = "Resolve"),
	STAT_INTELLIGENCE		UMETA(DisplayName = "Intelligence"),
	STAT_VITALITY			UMETA(DisplayName = "Vitality"),
	STAT_EXPERTISE			UMETA(DisplayName = "Expertise"),
	STAT_MAX
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class EXM_API UExmStatsComponent : public UBaseComponent
{
	GENERATED_BODY()

public:
	UExmStatsComponent();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<TEnumAsByte<EStatTypes>, int> stats;

	virtual EComponentTypes GetComponentType() const override
	{
		return COMPONENT_STATS;
	}
};

inline UExmStatsComponent::UExmStatsComponent()
{
}
