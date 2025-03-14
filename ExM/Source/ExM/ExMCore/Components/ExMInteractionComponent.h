// © 2024 Necrotek Labs. All rights reserved. ExMORTALIS, including its title, logo, concept, storyline, and associated assets, is a trademark of Necrotek Labs. Unauthorized use, distribution, or reproduction of any part of this game or its materials is strictly prohibited. All other trademarks and trade names are the property of their respective owners. For inquiries, please contact necroteklabs@gmail.com.

#pragma once

#include "CoreMinimal.h"
#include "BaseComponent.h"
#include "Components/ActorComponent.h"
#include "ExMInteractionComponent.generated.h"


class UPhysicsHandleComponent;
class AExMCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHoverInteractable, FString, displayName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCarry, UPrimitiveComponent*, carriedComponent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRelease);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnThrow);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClearInteractable);

UENUM()
enum EInteractionType
{
	INTERACTION_NONE,
	INTERACTION_CARRY,
	INTERACTION_USE
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXM_API UExMInteractionComponent : public UBaseComponent
{
	GENERATED_BODY()

public:	
	UExMInteractionComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* InteractionAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float interactionDistance;

	void Interact();

	UPROPERTY(BlueprintAssignable)
	FOnHoverInteractable OnHoverInteractable;

	UPROPERTY(BlueprintAssignable)
	FOnClearInteractable OnClearInteractable;

	UPROPERTY(BlueprintAssignable)
	FOnCarry OnCarry;
	UPROPERTY(BlueprintAssignable)
	FOnRelease OnRelease;
	UPROPERTY(BlueprintAssignable)
	FOnThrow OnThrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TEnumAsByte<EInteractionType> currentInteractionType;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPrimitiveComponent* grabbedComponent;

	UPhysicsHandleComponent* physicsHandleComponent;
	
	virtual EComponentTypes GetComponentType() const override
	{
		return COMPONENT_INTERACTION;
	}
protected:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	AExMCharacter* character;

	AActor* currentHoveredInteractable;

};
