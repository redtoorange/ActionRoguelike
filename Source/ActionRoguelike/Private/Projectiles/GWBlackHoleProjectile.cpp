#include "Projectiles/GWBlackHoleProjectile.h"

AGWBlackHoleProjectile::AGWBlackHoleProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGWBlackHoleProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AGWBlackHoleProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
