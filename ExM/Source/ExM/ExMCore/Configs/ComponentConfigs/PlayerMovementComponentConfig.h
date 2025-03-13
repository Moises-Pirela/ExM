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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess = "true"))
	float crouchCapsuleHeight = 60;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess = "true"))
	float standCapsuleHeight = 90;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess = "true"))
	float stanceChangeSpeed = 10;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess = "true"))
	float crouchEyeHeight = 20;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess = "true"))
	float standEyeHeight = 50;

	virtual FEntityComponent* CreateComponent() override
	{
		FBuffableFloat movementSpeed = FBuffableFloat{};
		movementSpeed.SetBaseValue(baseMovementSpeed);

		float initalTargetHeight = standCapsuleHeight;

		return new FPlayerMovementComponent{
			.targetStanceCapsuleHeight = initalTargetHeight,
			.movementSpeed = movementSpeed
		};
	};

	virtual UStruct* GetComponentTypeId() override
	{
		return FPlayerMovementComponent::StaticStruct();
	};
};
