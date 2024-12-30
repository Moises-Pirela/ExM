// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ExMCore/Utils/Exmortalis.h"
#include "GameFramework/GameModeBase.h"
#include "ExMGameMode.generated.h"


class UEntitySubsystem;
class UEntity;
struct FComponentArray;
class UExmStatsComponent;
class EntityContainer;

UCLASS(minimalapi)
class AExMGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AExMGameMode();

	UEntitySubsystem *entitySubsystem;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

private:
};





