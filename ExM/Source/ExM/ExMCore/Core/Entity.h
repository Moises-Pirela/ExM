#pragma once

#include "CoreMinimal.h"
#include "Entity.generated.h"

class UBaseComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UEntity : public UActorComponent
{
	GENERATED_BODY()

public:
	UEntity(){ entityId = -1;};

	int entityId;

	TArray<UBaseComponent*> GetComponents()
	{
		auto components = TArray<UBaseComponent*>{};

		GetOwner()->GetComponents<UBaseComponent*>(components);
		
		return components;
	}
};
