#pragma once

#include "CoreMinimal.h"
#include "ExM/ExMCore/Components/BuffableComponent.h"
#include "BuffDataTableRow.generated.h"

USTRUCT(BlueprintType)
struct FBuffDataTableRow : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
	TEnumAsByte<EBuffType> BuffType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
	TEnumAsByte<EAttributeTypes> AffectedAttribute;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
	TEnumAsByte<EDerivedStatTypes> AffectedDerivedStat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
	TEnumAsByte<EBuffApplicationType> BuffApplication;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
	TEnumAsByte<EBuffDuplicationType> BuffDuplication;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
	float Amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
	float Duration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
	int32 MaxStacks;
	
	int id;
};
