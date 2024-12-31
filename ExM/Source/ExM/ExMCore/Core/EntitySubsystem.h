// © 2024 Necrotek Labs. All rights reserved. ExMORTALIS, including its title, logo, concept, storyline, and associated assets, is a trademark of Necrotek Labs. Unauthorized use, distribution, or reproduction of any part of this game or its materials is strictly prohibited. All other trademarks and trade names are the property of their respective owners. For inquiries, please contact necroteklabs@gmail.com.

#pragma once

#include "CoreMinimal.h"
#include "EntityContainer.h"
#include "IPostProcessEvent.h"
#include "ExM/ExMCore/Systems/Systems.h"
#include "Subsystems/WorldSubsystem.h"
#include "EntitySubsystem.generated.h"

struct FComponentArray;
class UEntity;
class EntityContainer;
/**
 * 
 */

UCLASS()
class EXM_API UEntitySubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual void Tick(float deltaTime) override;
	
	void OnCreateEntity(UEntityConfig* entityConfig, int entityId, UEntity* startingEntity = nullptr);
	void SendPostprocessEvent(IPostProcessEvent* postProcessEvent);
	void OnKillEntity(int entityId);
	virtual TStatId GetStatId() const override;

	UFUNCTION(BlueprintCallable)
	void SpawnUnrealEntity(TSoftClassPtr<AActor> entityActor);
	UFUNCTION(BlueprintCallable)
	bool GetComponentByUSTRUCT(FName structName, int entityId, FEntityComponent& component);

	EntityContainer* entityContainer;
	
	TMap<ESystemTickType, TArray<TStrongObjectPtr<USystemBase>>> systems;
};
