// © 2024 Necrotek Labs. All rights reserved. ExMORTALIS, including its title, logo, concept, storyline, and associated assets, is a trademark of Necrotek Labs. Unauthorized use, distribution, or reproduction of any part of this game or its materials is strictly prohibited. All other trademarks and trade names are the property of their respective owners. For inquiries, please contact necroteklabs@gmail.com.


#include "ExmWeaponTagComponent.h"
#include "ExmDamageComponent.h"
#include "ExMHealthComponent.h"
#include "ExM/ExMCharacter.h"
#include "Kismet/KismetMathLibrary.h"


UExmWeaponTagComponent::UExmWeaponTagComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UExmWeaponTagComponent::BeginPlay()
{
	Super::BeginPlay();

	damageComponent = GetOwner()->GetComponentByClass<UExmDamageComponent>();
	weaponSkelMesh  = GetOwner()->GetComponentByClass<USkeletalMeshComponent>();
}

void UExmWeaponTagComponent::Fire(FVector startLocation, FVector direction)
{
	if (nextShotTime > GetOwner()->GetWorld()->GetTimeSeconds()) return;
	
	switch (weaponType)
	{
	case WEAPON_TYPE_HITSCAN:
		HitscanFire(startLocation, direction);
		break;
	case WEAPON_TYPE_MELEE:
		StartMelee(armsFire);
		break;
	case WEAPON_TYPE_PROJECTILE:
		ProjectileFire(startLocation, direction);
		break;
	}

	nextShotTime =  GetOwner()->GetWorld()->GetTimeSeconds() + fireRateSeconds;
}

void UExmWeaponTagComponent::HitscanFire(FVector startLocation, FVector direction)
{
	wielder->GetMesh1P()->GetAnimInstance()->Montage_Play(armsFire);

	if (weaponSkelMesh)
		weaponSkelMesh->GetAnimInstance()->Montage_Play(weaponFire);
	
	const FVector cameraLocation = startLocation;
	const FVector cameraViewDirection = direction;

	FHitResult hitResult;
	FCollisionQueryParams TraceParams(FName(TEXT("LineTrace")), true, GetOwner()->GetOwner());
	TraceParams.bTraceComplex = false;
	TraceParams.bReturnPhysicalMaterial = true;

	for (int i = 0; i < roundsPerShot; i++)
	{
		const FVector spreadVector = UKismetMathLibrary::RandomUnitVectorInConeInDegrees(cameraViewDirection, weaponSpread);

		const FVector endPoint = cameraLocation + (spreadVector * weaponRange);
		
		bool bHit = GetOwner()->GetWorld()->LineTraceSingleByChannel(hitResult, cameraLocation, endPoint, ECC_Visibility, TraceParams);

		FColor lineColor = bHit ? FColor::Green : FColor::Red; // Green for hit, Red for miss
		
		DrawDebugLine(GetWorld(), cameraLocation, endPoint, lineColor, false, 1.0f, 0, 1.0f);

		if (!hitResult.bBlockingHit) return;
		
		FVector hitLocation = hitResult.ImpactPoint;
		FVector boxSize = FVector(5.0f, 5.0f, 5.0f);
		FColor boxColor = FColor::Blue;
		DrawDebugBox(GetWorld(), hitLocation, boxSize, FQuat::Identity, boxColor, false, 1.0f, 0, 1.0f);

		AActor* hitActor = hitResult.GetActor();

		if (hitActor)
		{
			UExMHealthComponent* healthComponent = hitActor->GetComponentByClass<UExMHealthComponent>();
		
			if (healthComponent)
			{
				FDamageData damage;

				damage.baseDamage = damageComponent->baseDamage;
				damage.damageType = damageComponent->damageType;
			
				healthComponent->TakeDamage(damage);
			}
		}
	}
}

void UExmWeaponTagComponent::ProjectileFire(FVector startLocation, FVector direction)
{
}

void UExmWeaponTagComponent::StartMelee(UAnimMontage* meleeMontage)
{
	wielder->GetMesh1P()->GetAnimInstance()->Montage_Play(meleeMontage);
}

void UExmWeaponTagComponent::AltFire(FVector startLocation, FVector direction)
{
	switch (weaponType)
	{
	case WEAPON_TYPE_MELEE:
		StartMelee(altArmsFire);
		break;
	}
}

void UExmWeaponTagComponent::FinishMelee(FVector startLocation, FVector direction)
{
	const FVector cameraLocation = startLocation;
	const FVector cameraViewDirection = direction;

	const FVector endPoint = cameraLocation + (cameraViewDirection * weaponRange);

	FHitResult hitResult;
	FCollisionQueryParams TraceParams(FName(TEXT("LineTrace")), true, GetOwner()->GetOwner());
	TraceParams.bTraceComplex = false;
	TraceParams.bReturnPhysicalMaterial = true;

	GetOwner()->GetWorld()->LineTraceSingleByChannel(hitResult, cameraLocation, endPoint, ECC_Visibility, TraceParams);

	if (!hitResult.bBlockingHit) return;

	AActor* hitActor = hitResult.GetActor();

	if (hitActor)
	{
		UExMHealthComponent* healthComponent = hitActor->GetComponentByClass<UExMHealthComponent>();

		if (healthComponent)
		{
			FDamageData damage;

			damage.baseDamage = damageComponent->baseDamage;
			damage.damageType = damageComponent->damageType;

			healthComponent->TakeDamage(damage);
		}
	}
}
