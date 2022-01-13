#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GWBaseProjectile.generated.h"

UCLASS(Abstract)
class ACTIONROGUELIKE_API AGWBaseProjectile : public AActor
{
	GENERATED_BODY()

public:
	AGWBaseProjectile();

	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	class UProjectileMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	class UParticleSystemComponent* EffectComponent;

	UPROPERTY(EditDefaultsOnly, Category="Effects")
	UParticleSystem* ImpactVFX;

	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                        FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Explode();
};
