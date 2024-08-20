// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ExMGameMode.generated.h"


class EntityContainer;

UCLASS(minimalapi)
class AExMGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AExMGameMode();

	virtual void BeginPlay() override;
};





