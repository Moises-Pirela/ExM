// © 2024 Necrotek Labs. All rights reserved. ExMORTALIS, including its title, logo, concept, storyline, and associated assets, is a trademark of Necrotek Labs. Unauthorized use, distribution, or reproduction of any part of this game or its materials is strictly prohibited. All other trademarks and trade names are the property of their respective owners. For inquiries, please contact necroteklabs@gmail.com.

#pragma once

#include "CoreMinimal.h"
#include "BaseComponent.h"
#include "ExmStatsComponent.h"
#include "ExM/ExMCore/ExmGameInstance.h"
#include "BuffableComponent.generated.h"



UENUM(BlueprintType)
enum EBuffType
{
	BUFF_STRENGTH,
	BUFF_INTELLIGENCE,
	BUFF_DEXTERITY,
	BUFF_MOVEMENT_SPEED,
	BUFF_JUMP_FORCE,

	BUFF_MAX
};

UENUM(BlueprintType)
enum EBuffApplicationType
{
	APPLICATION_BASE,
	APPLICATION_FLAT,
	APPLICATION_PERCENTAGE
};

UENUM(BlueprintType)
enum EBuffDuplicationType
{
	DUPLICATION_IGNORE,
	DUPLICATION_STACK,
	DUPLICATION_EXTEND
};

USTRUCT(BlueprintType)
struct FBuff
{
	GENERATED_BODY()

	EBuffType buffType;
	EAttributeTypes affectedAttribute;
	EDerivedStatTypes affectedDerivedStat;
	EBuffApplicationType buffApplication;
	EBuffDuplicationType BuffDuplication;

	float amount;
	float stacks;
	float expireTimeSecs;
};

inline void ApplyBaseBuff(float& val, float amount, int stacks)
{
	val = amount * stacks;
}

inline void ApplyFlatBuff(float& val, float amount, int stacks)
{
	val += amount * stacks;
}

inline void ApplyPercentageBuff(float& val, float amount, float baseVal, int stacks)
{
	val += (baseVal * amount / 100.0f) * stacks;
}

inline void ApplyBuff(EBuffApplicationType applicationType, float& val, float amount, float baseVal, int stacks)
{
	switch (applicationType) {
	case APPLICATION_BASE:
		ApplyBaseBuff(val, amount,stacks);
		break;
	case APPLICATION_FLAT:
		ApplyFlatBuff(val, amount,stacks);
		break;
	case APPLICATION_PERCENTAGE:
		ApplyPercentageBuff(val, amount, baseVal, stacks);
		break;
	}
}

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class EXM_API UExmBuffableComponent : public UBaseComponent
{
	GENERATED_BODY()

public:
	UExmBuffableComponent();

	FBuff* buffs[BUFF_MAX];

protected:
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable)
	void AddBuff(const int id);

	virtual EComponentTypes GetComponentType() const override
	{
		return COMPONENT_BUFFABLE;
	}
};
