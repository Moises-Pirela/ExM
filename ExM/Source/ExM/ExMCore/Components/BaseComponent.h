// © 2024 Necrotek Labs. All rights reserved. ExMORTALIS, including its title, logo, concept, storyline, and associated assets, is a trademark of Necrotek Labs. Unauthorized use, distribution, or reproduction of any part of this game or its materials is strictly prohibited. All other trademarks and trade names are the property of their respective owners. For inquiries, please contact necroteklabs@gmail.com.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseComponent.generated.h"


UENUM(BlueprintType)
enum EComponentTypes
{
	COMPONENT_NONE               = 0      	UMETA(DisplayName = "None"), 
	COMPONENT_WEAPON_TAG         = 1 << 0 	UMETA(DisplayName = "Weapon"),
	COMPONENT_WEAPON_MELEE       = 1 << 1 	UMETA(DisplayName = "Melee Weapon"),
	COMPONENT_WEAPON_HITSCAN     = 1 << 2 	UMETA(DisplayName = "Hitscan Weapon"),
	COMPONENT_WEAPON_PROJECTILE  = 1 << 3 	UMETA(DisplayName = "Projectile Weapon"),
	COMPONENT_HEALTH             = 1 << 4 	UMETA(DisplayName = "Health"),
	COMPONENT_INTERACTION        = 1 << 5 	UMETA(DisplayName = "Interaction"),
	COMPONENT_RESISTANCES        = 1 << 6 	UMETA(DisplayName = "Resistances"),
	COMPONENT_DAMAGE             = 1 << 7 	UMETA(DisplayName = "Damage"),
	COMPONENT_EQUIPMENT          = 1 << 8 	UMETA(DisplayName = "Equipment"),
	COMPONENT_JUMP               = 1 << 9 	UMETA(DisplayName = "Jump"),
	COMPONENT_STATS              = 1 << 10 	UMETA(DisplayName = "Stats"),
	COMPONENT_INVENTORY          = 1 << 11 	UMETA(DisplayName = "Inventory"),
	COMPONENT_BUFFABLE           = 1 << 12 	UMETA(DisplayName = "Buffable"),
	COMPONENT_BUFF               = 1 << 13 	UMETA(DisplayName = "Buff"),

	COMPONENT_MAX                = 1 << 14	UMETA(Hidden), // Set to the next power of 2
};


UCLASS(Abstract, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXM_API	UBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBaseComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int owningEntityId;
	
	virtual EComponentTypes GetComponentType() const PURE_VIRTUAL(UBaseComponent::GetComponentType, return EComponentTypes::COMPONENT_WEAPON_TAG;);
};
