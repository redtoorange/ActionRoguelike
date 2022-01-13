#pragma once

#include "CoreMinimal.h"
#include "GWBaseProjectile.h"
#include "GWDashProjectile.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AGWDashProjectile : public AGWBaseProjectile
{
	GENERATED_BODY()

public:
	AGWDashProjectile();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float effectTime = 0.2f;

	UPROPERTY(EditAnywhere)
	float teleportTime = 0.4f;
	
	UFUNCTION()
	void EffectTimerElapsed();

	UFUNCTION()
	void TeleportTimerElapsed();

	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit) override;

public:
	virtual void Explode_Implementation() override;
private:
	FTimerHandle EffectTimer;
	FTimerHandle TeleportTimer;
};
