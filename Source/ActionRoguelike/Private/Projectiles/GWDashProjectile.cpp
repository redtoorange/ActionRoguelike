#include "Projectiles/GWDashProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


AGWDashProjectile::AGWDashProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGWDashProjectile::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->IgnoreActorWhenMoving(GetInstigator(), true);
	SphereComponent->OnComponentHit.AddDynamic(this, &AGWDashProjectile::OnComponentHit);
	GetWorldTimerManager().SetTimer(EffectTimer, this, &AGWDashProjectile::EffectTimerElapsed, effectTime, false);
}

void AGWDashProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// The timer has run out, so stop the projectile and teleport the player
void AGWDashProjectile::EffectTimerElapsed()
{
	MovementComponent->StopMovementImmediately();
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TeleportEffect, GetActorTransform());
	GetWorldTimerManager().SetTimer(TeleportTimer, this, &AGWDashProjectile::TeleportTimerElapsed, teleportTime, false);
}

void AGWDashProjectile::TeleportTimerElapsed()
{
	GetInstigator()->TeleportTo(GetActorLocation(), GetInstigator()->GetActorRotation());
	Destroy();
}

// If we hit the world, then we want to stop immediately and start the effect
void AGWDashProjectile::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(Hit.GetActor() != GetInstigator())
	{
		GetWorldTimerManager().ClearTimer(EffectTimer);
		MovementComponent->StopMovementImmediately();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TeleportEffect, GetActorTransform());
		GetWorldTimerManager().SetTimer(TeleportTimer, this, &AGWDashProjectile::TeleportTimerElapsed, teleportTime, false);
	}
}
