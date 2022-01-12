#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GWBaseProjectile.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AGWBaseProjectile : public AActor
{
	GENERATED_BODY()

public:
	AGWBaseProjectile();

	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UProjectileMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UParticleSystemComponent* EffectComponent;
};
