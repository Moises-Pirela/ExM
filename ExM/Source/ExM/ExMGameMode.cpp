// Copyright Epic Games, Inc. All Rights Reserved.

#include "ExMGameMode.h"
#include "ExMCharacter.h"
#include "ExMCore/Core/EntitySubsystem.h"
#include "ExMCore\Core\EntityContainer.h"
#include "UObject/ConstructorHelpers.h"

AExMGameMode::AExMGameMode()
	: Super()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	PrimaryActorTick.bCanEverTick = true;
}

void AExMGameMode::BeginPlay()
{
	Super::BeginPlay();

	entitySubsystem = GetWorld()->GetSubsystem<UEntitySubsystem>();
}

void AExMGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
