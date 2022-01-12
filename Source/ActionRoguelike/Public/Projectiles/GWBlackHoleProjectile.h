#pragma once

#include "CoreMinimal.h"
#include "GWBaseProjectile.h"
#include "GWBlackHoleProjectile.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AGWBlackHoleProjectile : public AGWBaseProjectile
{
	GENERATED_BODY()

public:
	AGWBlackHoleProjectile();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
};
