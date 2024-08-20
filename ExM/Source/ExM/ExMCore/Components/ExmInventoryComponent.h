#pragma once
#include "CoreMinimal.h"
#include "BaseComponent.h"
#include "ExmInventoryComponent.generated.h"

class UExmWeaponTagComponent;

USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_BODY()
	
	int configID;

	FInventoryItem(const int _configId = -1)
	{
		configID = _configId;
	}

};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UExmInventoryComponent : public UBaseComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int inventorySizeX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int inventorySizeY;
	
	UExmWeaponTagComponent *availableWeapons[5];
	FInventoryItem *inventorySlots;
	
	int32 GetIndex(int32 x, int32 y) const
	{
		return x + y * inventorySizeX;
	}

	UFUNCTION(BlueprintCallable)
	FInventoryItem& GetItem(int32 x, int32 y)
	{
		return inventorySlots[GetIndex(x, y)];
	}

	UFUNCTION(BlueprintCallable)
	int32 GetInventorySize()
	{
		return inventorySizeX * inventorySizeY;
	}

protected:
	virtual void BeginPlay() override;
};





