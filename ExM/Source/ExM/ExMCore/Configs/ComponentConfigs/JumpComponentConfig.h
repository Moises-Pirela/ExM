// © 2024 Necrotek Labs. All rights reserved. ExMORTALIS, including its title, logo, concept, storyline, and associated assets, is a trademark of Necrotek Labs. Unauthorized use, distribution, or reproduction of any part of this game or its materials is strictly prohibited. All other trademarks and trade names are the property of their respective owners. For inquiries, please contact necroteklabs@gmail.com.
#pragma once
#include "CoreMinimal.h"
#include "ExM/ExMCore/Core/EntityComponent.h"
#include "ExM/ExMCore/Core/EntityComponentConfig.h"
#include "JumpComponentConfig.generated.h"

UCLASS(EditInlineNew, BlueprintType)
class EXM_API UJumpComponentConfig : public UEntityComponentConfigBase {
	
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float jumpSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float maxJumps;
	
	virtual FEntityComponent* CreateComponent() override
	{
		return new FJumpComponent();
	}
	virtual UStruct* GetComponentTypeId() override
	{
		return FJumpComponent::StaticStruct();
	}
};