#pragma once

#include "CoreMinimal.h"
#include "GWBaseProjectile.h"
#include "GWMagicProjectile.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AGWMagicProjectile : public AGWBaseProjectile
{
	GENERATED_BODY()

public:
	AGWMagicProjectile();

	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;

protected:
	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* Actor, UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg, const FHitResult& HitResult);
	
	virtual void BeginPlay() override;
};
