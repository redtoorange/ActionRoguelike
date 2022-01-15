#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UAudioComponent* AudioComponent;

	UPROPERTY(EditDefaultsOnly, Category="Effects")
	UParticleSystem* ImpactVFX;
	
	UPROPERTY(EditDefaultsOnly, Category="Effects")
	USoundCue* ImpactSoundFx;

	UPROPERTY(EditDefaultsOnly, Category="Effects")
	TSubclassOf<UCameraShakeBase> CameraShake;
	
	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                        FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Explode();
};
