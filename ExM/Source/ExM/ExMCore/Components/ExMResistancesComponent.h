#pragma once

#include "CoreMinimal.h"
#include "ExMResistancesComponent.generated.h"

enum EDamageTypes : int;

UCLASS(ClassGroup=(ExMortalis), meta=(BlueprintSpawnableComponent))
class EXM_API UExMResistancesComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UExMResistancesComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<TEnumAsByte<EDamageTypes>, float> Resistances;
	
protected:
	virtual void BeginPlay() override;
};
