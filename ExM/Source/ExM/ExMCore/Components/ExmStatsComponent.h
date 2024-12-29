#pragma once


#include "CoreMinimal.h"
#include "BaseComponent.h"
#include "ExM/ExMCore/Buffables.h"
#include "ExM/ExMCore/Utils/StatHelpers.h"
#include "ExmStatsComponent.generated.h"

UENUM(BlueprintType)
enum EAttributeTypes
{
	ATTRIBUTE_DEXTERITY			UMETA(DisplayName = "Dexterity"),
	ATTRIBUTE_STRENGTH			UMETA(DisplayName = "Strength"),
	ATTRIBUTE_INTELLIGENCE		UMETA(DisplayName = "Intelligence"),
	ATTRIBUTE_MAX				UMETA(DisplayName = "None")
};

UENUM(BlueprintType)
enum EDerivedStatTypes
{
	DERIVED_STAT_MOVEMENT_SPEED        	UMETA(DisplayName = "Movement Speed"),
	DERIVED_STAT_SPRINT_SPEED          	UMETA(DisplayName = "Sprint Speed"),
	DERIVED_STAT_RELOAD_SPEED          	UMETA(DisplayName = "Reload Speed"),
	DERIVED_STAT_JUMP_FORCE            	UMETA(DisplayName = "Jump Force"),
	DERIVED_STAT_THROW_FORCE           	UMETA(DisplayName = "Throw Force"),
	DERIVED_STAT_MELEE_DAMAGE          	UMETA(DisplayName = "Melee Damage"),
	DERIVED_STAT_ATTACK_SPEED          	UMETA(DisplayName = "Attack Speed"),
	DERIVED_STAT_PROJECTILE_SPEED      	UMETA(DisplayName = "Projectile Speed"),
	DERIVED_STAT_PROJECTILE_DAMAGE     	UMETA(DisplayName = "Projectile Damage"),
	DERIVED_STAT_MAX_HEALTH            	UMETA(DisplayName = "Max Health"),
	DERIVED_STAT_HEALTH_REGEN          	UMETA(DisplayName = "Health Regeneration"),
	DERIVED_STAT_CRITICAL_HIT_DAMAGE   	UMETA(DisplayName = "Critical Hit Damage"),
	DERIVED_STAT_STAMINA               	UMETA(DisplayName = "Stamina"),
	DERIVED_STAT_STAMINA_REGEN         	UMETA(DisplayName = "Stamina Regeneration"),
	DERIVED_STAT_FIRE_RATE				UMETA(DisplayName = "Fire Rate"),
	DERIVED_STAT_WEAPON_DAMAGE			UMETA(DisplayName = "Weapon Damage"),

	DERIVED_STAT_KINETIC_RESISTANCE		UMETA(DisplayName = "Kinetic Resistance"),
	DERIVED_STAT_BLUNT_RESISTANCE		UMETA(DisplayName = "Blunt Resistance"),
	DERIVED_STAT_SLASH_RESISTANCE		UMETA(DisplayName = "Slash Resistance"),
	DERIVED_STAT_NECROTIC_RESISTANCE	UMETA(DisplayName = "Necrotic Resistance"),
	DERIVED_STAT_FALL_DAMAGE_RESISTANCE	UMETA(DisplayName = "Fall Damage Resistance"),

	DERIVED_STAT_MAX					UMETA(DisplayName = "None")
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class EXM_API UExmStatsComponent : public UBaseComponent
{
	GENERATED_BODY()

public:
	UExmStatsComponent();

	void SetDerivedStats();

	void Init();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<TEnumAsByte<EAttributeTypes>, FBuffableInt> attributes;
	float attributeModifiers[ATTRIBUTE_MAX];
	
	FBuffableFloat derivedStats[DERIVED_STAT_MAX];
	float derivedStatModifiers[DERIVED_STAT_MAX];

	virtual EComponentTypes GetComponentType() const override
	{
		return COMPONENT_STATS;
	}
};


