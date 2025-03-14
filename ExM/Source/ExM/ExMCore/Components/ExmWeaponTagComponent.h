// © 2024 Necrotek Labs. All rights reserved. ExMORTALIS, including its title, logo, concept, storyline, and associated assets, is a trademark of Necrotek Labs. Unauthorized use, distribution, or reproduction of any part of this game or its materials is strictly prohibited. All other trademarks and trade names are the property of their respective owners. For inquiries, please contact necroteklabs@gmail.com.

#pragma once

#include "CoreMinimal.h"
#include "BaseComponent.h"
#include "Components/ActorComponent.h"
#include "ExmWeaponTagComponent.generated.h"

class AExMCharacter;
class UExmDamageComponent;

UENUM()
enum EWeaponTypes : int
{
	WEAPON_TYPE_HITSCAN,
	WEAPON_TYPE_PROJECTILE,
	WEAPON_TYPE_MELEE
};

UENUM(BlueprintType)
enum EWeapons : int
{
	WEAPON_FISTS,
	WEAPON_SAW,
	WEAPON_C93,
	WEAPON_M1893,
	WEAPON_MAC,
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class EXM_API UExmWeaponTagComponent : public UBaseComponent
{
	GENERATED_BODY()

public:
	UExmWeaponTagComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AExMCharacter* wielder;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* weaponSkelMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Weapon")
	TEnumAsByte<EWeapons> weapon;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Weapon")
	TEnumAsByte<EWeaponTypes> weaponType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Weapon")
	float weaponRange;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Weapon")
	float weaponSpread;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Weapon")
	float fireRateSeconds;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Weapon")
	FVector recoil;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Weapon", meta=(EditCondition = "weaponType != 2", EditConditionHides))
	int roundsPerShot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Weapon", meta=(EditCondition = "weaponType != 2", EditConditionHides))
	int maxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Weapon", meta=(EditCondition = "weaponType != 2", EditConditionHides))
	int magazineSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Weapon")
	FName slotName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon")
	bool bIsReloading;

	UExmDamageComponent* damageComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* armsFire;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* altArmsFire;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* weaponFire;

	virtual EComponentTypes GetComponentType() const override
	{
		return COMPONENT_WEAPON_TAG;
	}
	void Fire(FVector startLocation, FVector direction);
	void AltFire(FVector startLocation, FVector direction);
	UFUNCTION(BlueprintCallable)
	void FinishMelee(FVector startLocation, FVector direction);

private:
	float nextShotTime;

protected:
	void HitscanFire(FVector startLocation, FVector direction);
	void ProjectileFire(FVector startLocation, FVector direction);
	void StartMelee(UAnimMontage* meleeMontage);
	virtual void BeginPlay() override;
};
