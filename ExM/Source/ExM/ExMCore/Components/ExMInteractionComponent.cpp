// © 2024 Necrotek Labs. All rights reserved. ExMORTALIS, including its title, logo, concept, storyline, and associated assets, is a trademark of Necrotek Labs. Unauthorized use, distribution, or reproduction of any part of this game or its materials is strictly prohibited. All other trademarks and trade names are the property of their respective owners. For inquiries, please contact necroteklabs@gmail.com.
#include "ExMInteractionComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "ExM/ExMCharacter.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

UExMInteractionComponent::UExMInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UExMInteractionComponent::Interact()
{
	if (grabbedComponent)
	{
		physicsHandleComponent->ReleaseComponent();
		grabbedComponent->SetPhysicsLinearVelocity(FVector::Zero());
		grabbedComponent = nullptr;
		currentInteractionType = INTERACTION_NONE;
		return;
	}
	if (currentHoveredInteractable == nullptr) return;

	if (currentInteractionType == INTERACTION_NONE) return;

	if (currentInteractionType == INTERACTION_CARRY)
	{
		grabbedComponent = currentHoveredInteractable->GetComponentByClass<UPrimitiveComponent>();
		physicsHandleComponent->GrabComponentAtLocation(grabbedComponent, FName(), currentHoveredInteractable->GetActorLocation());
		currentHoveredInteractable = nullptr;
		OnClearInteractable.Broadcast();
		
	}
}

void UExMInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	physicsHandleComponent = GetOwner()->GetComponentByClass<UPhysicsHandleComponent>();

	character = Cast<AExMCharacter>(GetOwner());
	
	if (APlayerController* PlayerController = Cast<APlayerController>(character->GetController()))
	{
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			EnhancedInputComponent->BindAction(InteractionAction, ETriggerEvent::Triggered, this, &UExMInteractionComponent::Interact);
		}
	}
}

void UExMInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (grabbedComponent)
	{
		FVector _newLocation = character->GetFirstPersonCameraComponent()->GetComponentLocation() + character->GetFirstPersonCameraComponent()->GetForwardVector() * interactionDistance;
		
		physicsHandleComponent->SetTargetLocation(_newLocation);
		grabbedComponent->SetPhysicsAngularVelocityInDegrees(FVector::Zero());
	}

	UCameraComponent* _cameraComponent = character->GetFirstPersonCameraComponent();

	FVector Start = _cameraComponent->GetComponentLocation();
	FVector ForwardVector = _cameraComponent->GetForwardVector();
	
	FVector End = Start + (ForwardVector * interactionDistance);

	FHitResult HitResult;
	FCollisionQueryParams Params;
	
	Params.AddIgnoredActor(character);

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_GameTraceChannel1, Params);

	if (bHit)
	{
		AActor* _hitActor = HitResult.GetActor();

		if (_hitActor == currentHoveredInteractable) return;
		
		if (_hitActor)
		{
			UStaticMeshComponent* _staticMesh =  _hitActor->GetComponentByClass<UStaticMeshComponent>();

			if (_staticMesh)
			{
				if (_staticMesh->IsSimulatingPhysics())
				{
					currentInteractionType = EInteractionType::INTERACTION_CARRY;
				}
			}
			
			currentHoveredInteractable = _hitActor;

			OnHoverInteractable.Broadcast(_hitActor->GetName());

			return;
		}
	}

	currentHoveredInteractable = nullptr;

	OnClearInteractable.Broadcast();
}

