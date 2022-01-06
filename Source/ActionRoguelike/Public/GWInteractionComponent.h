#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GWInteractionComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API UGWInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void PrimaryInteract();
	
	UGWInteractionComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
