// © 2024 Necrotek Labs. All rights reserved. ExMORTALIS, including its title, logo, concept, storyline, and associated assets, is a trademark of Necrotek Labs. Unauthorized use, distribution, or reproduction of any part of this game or its materials is strictly prohibited. All other trademarks and trade names are the property of their respective owners. For inquiries, please contact necroteklabs@gmail.com.

#pragma once

#include "CoreMinimal.h"
#include "BaseComponent.h"
#include "ExmWeaponTagComponent.h"
#include "Components/ActorComponent.h"
#include "ExmEquipmentComponent.generated.h"


enum EWeapons : int;
class AExMCharacter;
class UExmWeaponTagComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXM_API UExmEquipmentComponent : public UBaseComponent
{
	GENERATED_BODY()

public:	
	UExmEquipmentComponent();
	
	UExmWeaponTagComponent* weaponSlots[10];
	int equippedWeaponIndex = -1;
	int prevWeaponIndex = -1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AActor> defaultWeapon;
	
protected:
	virtual void BeginPlay() override;

private:
	AExMCharacter* character;

public:
	virtual EComponentTypes GetComponentType() const override
	{
		return COMPONENT_EQUIPMENT;
	}
	void EquipWeapon(UExmWeaponTagComponent* weapon, int slot);
	void SwapWeapon(int weaponIndex);
	void FireWeapon();
	void SecondaryFire();

	UFUNCTION(BlueprintCallable)
	EWeapons GetEquippedWeapon() const
	{
		if(equippedWeaponIndex == -1 || weaponSlots[equippedWeaponIndex] == nullptr)
			return WEAPON_FISTS;
		
		return weaponSlots[equippedWeaponIndex]->weapon;
	}

	UFUNCTION(BlueprintCallable)
	UExmWeaponTagComponent* GetEquippedWeaponComponent() const
	{
		if(equippedWeaponIndex == -1 || weaponSlots[equippedWeaponIndex] == nullptr)
			return nullptr;
		
		return weaponSlots[equippedWeaponIndex];
	}
};
