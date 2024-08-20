#include "ExmInventoryComponent.h"

void UExmInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	int inventorySize = inventorySizeX * inventorySizeY;

	inventorySlots = new FInventoryItem[inventorySize];
	
	for (int32 i = 0; i < inventorySize; ++i)
	{
		inventorySlots[i] = FInventoryItem(-1);
	}

	UE_LOG(LogTemp, Warning, TEXT("Inventory Size: %d"), inventorySize);
}
