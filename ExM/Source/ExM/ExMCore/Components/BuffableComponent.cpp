// © 2024 Necrotek Labs. All rights reserved. ExMORTALIS, including its title, logo, concept, storyline, and associated assets, is a trademark of Necrotek Labs. Unauthorized use, distribution, or reproduction of any part of this game or its materials is strictly prohibited. All other trademarks and trade names are the property of their respective owners. For inquiries, please contact necroteklabs@gmail.com.


#include "BuffableComponent.h"

#include "ExmStatsComponent.h"
#include "ExM/ExMCore/Configs/BuffDataTableRow.h"
#include "ExM/ExMCore/Core/Entity.h"
#include "ExM/ExMCore/Core/EntityContainer.h"
#include "ExM/ExMCore/Core/EntitySubsystem.h"

UExmBuffableComponent::UExmBuffableComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UExmBuffableComponent::BeginPlay()
{
	Super::BeginPlay();
	
	AddBuff(0);
}

void UExmBuffableComponent::AddBuff(const int id)
{
	FBuffDataTableRow buffConfig = ((UExmGameInstance*)GetWorld()->GetGameInstance())->BuffDataArray[id];

	if (buffs[buffConfig.BuffType] == nullptr)
	{
		FBuff* newBuff = new FBuff;
		newBuff->stacks = 1;
		newBuff->affectedAttribute = buffConfig.AffectedAttribute;
		newBuff->buffApplication = buffConfig.BuffApplication;
		newBuff->affectedDerivedStat = buffConfig.AffectedDerivedStat;
		newBuff->BuffDuplication = buffConfig.BuffDuplication;
		newBuff->amount = buffConfig.Amount;
		newBuff->expireTimeSecs = GetWorld()->GetTimeSeconds() + buffConfig.Duration;
		buffs[buffConfig.BuffType] = newBuff;
		return;
	}

	switch (buffConfig.BuffDuplication)
	{
	case DUPLICATION_IGNORE:
		return;
	case DUPLICATION_STACK:
		buffs[buffConfig.BuffType]->stacks = FMath::Clamp(buffs[buffConfig.BuffType]->stacks + 1, 0, buffConfig.MaxStacks);
		break;
	case DUPLICATION_EXTEND:
		buffs[buffConfig.BuffType]->expireTimeSecs += GetWorld()->GetTimeSeconds() + buffConfig.Duration;
		break;
	}
}
