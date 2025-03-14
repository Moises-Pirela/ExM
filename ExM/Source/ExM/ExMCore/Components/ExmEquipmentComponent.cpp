// © 2024 Necrotek Labs. All rights reserved. ExMORTALIS, including its title, logo, concept, storyline, and associated assets, is a trademark of Necrotek Labs. Unauthorized use, distribution, or reproduction of any part of this game or its materials is strictly prohibited. All other trademarks and trade names are the property of their respective owners. For inquiries, please contact necroteklabs@gmail.com.
#include "ExmEquipmentComponent.h"

#include "Camera/CameraComponent.h"
#include "ExM/ExMCharacter.h"
#include "ExmWeaponTagComponent.h"

UExmEquipmentComponent::UExmEquipmentComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UExmEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	equippedWeaponIndex = -1;
	prevWeaponIndex = -1;
	
	character = Cast<AExMCharacter>(GetOwner());
	
	const FTransform transform = character->GetMesh1P()->GetSocketTransform("Prop_R", RTS_World);

	FActorSpawnParameters spawnParameters;

	spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AActor* weaponActor = character->GetWorld()->SpawnActor(defaultWeapon, &transform, spawnParameters);

	auto weaponComponent = weaponActor->GetComponentByClass<UExmWeaponTagComponent>();

	EquipWeapon(weaponComponent, 0);
}

void UExmEquipmentComponent::EquipWeapon(UExmWeaponTagComponent* weapon, int slot)
{
	if (equippedWeaponIndex != -1)
	{
		weaponSlots[equippedWeaponIndex]->GetOwner()->SetActorHiddenInGame(true);
	}

	if (weaponSlots[slot] != nullptr)
	{
		//TODO: What to do with weapon here?
	}

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	
	weapon->GetOwner()->AttachToComponent(character->GetMesh1P(), AttachmentRules, weapon->slotName);

	weapon->wielder = character;
	
	weaponSlots[slot] = weapon;

	equippedWeaponIndex = slot;
}

void UExmEquipmentComponent::SwapWeapon(int weaponIndex)
{
	if (weaponSlots[weaponIndex] == nullptr) return;

	weaponSlots[weaponIndex]->GetOwner()->SetActorHiddenInGame(false);
	weaponSlots[equippedWeaponIndex]->GetOwner()->SetActorHiddenInGame(true);

	equippedWeaponIndex = weaponIndex;
}

void UExmEquipmentComponent::FireWeapon()
{
	weaponSlots[equippedWeaponIndex]->Fire(character->GetFirstPersonCameraComponent()->GetComponentLocation(), character->GetFirstPersonCameraComponent()->GetForwardVector());
}

void UExmEquipmentComponent::SecondaryFire()
{
	weaponSlots[equippedWeaponIndex]->AltFire(character->GetFirstPersonCameraComponent()->GetComponentLocation(), character->GetFirstPersonCameraComponent()->GetForwardVector());
}

