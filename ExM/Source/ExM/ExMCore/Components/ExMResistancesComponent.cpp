#include "ExMResistancesComponent.h"

UExMResistancesComponent::UExMResistancesComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UExMResistancesComponent::BeginPlay()
{
	UActorComponent::BeginPlay();
}
