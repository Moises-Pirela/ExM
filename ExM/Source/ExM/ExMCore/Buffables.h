#pragma once

#include "CoreMinimal.h"
#include "Buffables.generated.h"

USTRUCT()
struct FBuffableVal
{
	GENERATED_BODY()

	virtual void ResetModifications() {};
};

USTRUCT(BlueprintType)
struct FBuffableFloat : public FBuffableVal
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float baseVal;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float modifiedVal;

	FBuffableFloat()
	   : baseVal(0.f), modifiedVal(0.f)
	{}

	float GetValue() const
	{
		return modifiedVal;
	}

	void SetBaseValue(const float newBaseVal)
	{
		baseVal = newBaseVal;
		modifiedVal = baseVal;
	}

	void ApplyFlatModifier(const float amount, const int stacks)
	{
		modifiedVal = baseVal + amount * stacks;
	}

	void ApplyPercentageModifier(const float percent, const int stacks)
	{
		modifiedVal += baseVal * (percent * stacks / 100.f);
	}

	virtual void ResetModifications() override
	{
		modifiedVal = baseVal;
	}
};

USTRUCT(BlueprintType)
struct FBuffableInt : public FBuffableVal
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int baseVal;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int modifiedVal;

	int GetValue() const
	{
		return modifiedVal;
	}

	void SetBaseValue(const int newBaseVal)
	{
		baseVal = newBaseVal;
		modifiedVal = baseVal;
	}

	void ApplyFlatModifier(const int amount, const int stacks)
	{
		modifiedVal = baseVal + amount * stacks;
	}

	void ApplyPercentageModifier(const float percent, const int stacks)
	{
		modifiedVal += FMath::RoundToInt(baseVal * (percent * stacks / 100.f));
	}

	virtual void ResetModifications() override
	{
		modifiedVal = baseVal;
	}
};
