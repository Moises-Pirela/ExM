// © 2024 Necrotek Labs. All rights reserved. ExMORTALIS, including its title, logo, concept, storyline, and associated assets, is a trademark of Necrotek Labs. Unauthorized use, distribution, or reproduction of any part of this game or its materials is strictly prohibited. All other trademarks and trade names are the property of their respective owners. For inquiries, please contact necroteklabs@gmail.com.

#pragma once

#include "CoreMinimal.h"
#include "BaseComponent.h"
#include "Components/ActorComponent.h"
#include "ExM/ExMCore/Buffables.h"
#include "ExMHealthComponent.generated.h"

class UExmStatsComponent;
enum EDamageTypes : int;
class UExMResistancesComponent;

USTRUCT(BlueprintType)
struct FDamageData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float baseDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* pDamageDealer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EDamageTypes> damageType;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDieSignature);

UCLASS(ClassGroup=(ExMORTALIS), meta=(BlueprintSpawnableComponent))
class EXM_API UExMHealthComponent : public UBaseComponent
{
	GENERATED_BODY()

public:
	UExMHealthComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBuffableFloat maxHealth;

	UPROPERTY(BlueprintAssignable)
	FOnDieSignature OnDie;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float currentHealth;

	UExMResistancesComponent* resistancesComponent;
	UExmStatsComponent* statsComponent;

protected:
	virtual void BeginPlay() override;

public:
	virtual EComponentTypes GetComponentType() const override
	{
		return COMPONENT_HEALTH;
	}


	void TakeDamage(const FDamageData& damageData);

	bool IsDead() { return currentHealth <= 0; }
};
