#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GWAttributeComponent.generated.h"

class UGWAttributeComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChange, AActor*, Instigator, UGWAttributeComponent*,
                                              OwningComponent, float, NewHealth, float, Delta);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API UGWAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UGWAttributeComponent();

	UFUNCTION(BlueprintCallable, Category="Attributes")
	bool ApplyHealthChange(float delta, AActor* Instigator);

	UPROPERTY(BlueprintAssignable)
	FOnHealthChange OnHealthChange;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	float health;

	// HealthMax, Stamina, Strength
};
