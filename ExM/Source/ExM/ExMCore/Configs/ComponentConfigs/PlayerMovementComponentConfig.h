#pragma once

#include "ExM/ExMCore/Core/EntityComponent.h"
#include "ExM/ExMCore/Core/EntityComponentConfig.h"
#include "PlayerMovementComponentConfig.generated.h"

UCLASS(EditInlineNew, BlueprintType)
class EXM_API UPlayerMovementComponentConfig : public UEntityComponentConfigBase {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float baseMovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float sprintModifier;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float crouchModifier;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float jumpVelocity;

	virtual FEntityComponent* CreateComponent() override
	{
		FBuffableFloat movementSpeed = FBuffableFloat{};
		movementSpeed.SetBaseValue(baseMovementSpeed);

		return new FPlayerMovementComponent{.movementSpeed = movementSpeed};
	};

	virtual UStruct* GetComponentTypeId() override
	{
		return FPlayerMovementComponent::StaticStruct();
	};
};
