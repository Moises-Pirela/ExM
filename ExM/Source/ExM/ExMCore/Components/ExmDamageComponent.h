// © 2024 Necrotek Labs. All rights reserved. ExMORTALIS, including its title, logo, concept, storyline, and associated assets, is a trademark of Necrotek Labs. Unauthorized use, distribution, or reproduction of any part of this game or its materials is strictly prohibited. All other trademarks and trade names are the property of their respective owners. For inquiries, please contact necroteklabs@gmail.com.

#pragma once

#include "CoreMinimal.h"
#include "BaseComponent.h"
#include "Components/ActorComponent.h"
#include "ExmDamageComponent.generated.h"

enum EDamageTypes : int;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class EXM_API UExmDamageComponent : public UBaseComponent
{
	GENERATED_BODY()

public:
	UExmDamageComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Damage")
	float baseDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Damage")
	TEnumAsByte<EDamageTypes> damageType;

	virtual EComponentTypes GetComponentType() const override
	{
		return COMPONENT_DAMAGE;
	}
	
protected:
	virtual void BeginPlay() override;
};
