#pragma once

#include "CoreMinimal.h"
#include "InvetoryItemDataAsset.generated.h"

UENUM(BlueprintType)
enum EInventoryItemType
{
	ITEM_CONSUMABLE UMETA(DisplayName = "Consumable"),
	ITEM_EQUIPPABLE UMETA(DisplayName = "Equippable"),
};

UCLASS(BlueprintType)
class UInventoryItemDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	TEnumAsByte<EInventoryItemType> ItemType;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	TSoftObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	int32 MaxStackSize = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	float Weight = 0.0f;
};

UCLASS(BlueprintType)
class UInventoryItemContainerDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	TArray<UInventoryItemDataAsset> items;
};