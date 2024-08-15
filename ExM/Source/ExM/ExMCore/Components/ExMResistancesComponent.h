#pragma once

#include "CoreMinimal.h"
#include "BaseComponent.h"
#include "ExMResistancesComponent.generated.h"

enum EDamageTypes : int;

UCLASS(ClassGroup=(ExMortalis), meta=(BlueprintSpawnableComponent))
class EXM_API UExMResistancesComponent : public UBaseComponent
{
	GENERATED_BODY()
	
public:
	UExMResistancesComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<TEnumAsByte<EDamageTypes>, float> Resistances;

	virtual EComponentTypes GetComponentType() const override
	{
		return COMPONENT_RESISTANCES;
	}
	
protected:
	virtual void BeginPlay() override;
};
