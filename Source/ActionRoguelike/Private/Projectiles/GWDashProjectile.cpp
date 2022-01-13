#include "Projectiles/GWDashProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


AGWDashProjectile::AGWDashProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent->InitialSpeed = 6000.0f;
}

void AGWDashProjectile::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->IgnoreActorWhenMoving(GetInstigator(), true);
	SphereComponent->OnComponentHit.AddDynamic(this, &AGWDashProjectile::OnActorHit);
	GetWorldTimerManager().SetTimer(EffectTimer, this, &AGWDashProjectile::EffectTimerElapsed, effectTime, false);
}

void AGWDashProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// The timer has run out, so stop the projectile and teleport the player
void AGWDashProjectile::EffectTimerElapsed()
{
	Explode();
}

void AGWDashProjectile::TeleportTimerElapsed()
{
	AActor* actorToTeleport = GetInstigator();
	if (actorToTeleport)
	{
		actorToTeleport->TeleportTo(GetActorLocation(), actorToTeleport->GetActorRotation(), false, false);
	}
	Destroy();
}

// If we hit the world, then we want to stop immediately and start the effect
void AGWDashProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (Hit.GetActor() != GetInstigator())
	{
		Explode();
	}
}

void AGWDashProjectile::Explode_Implementation()
{
	GetWorldTimerManager().ClearTimer(EffectTimer);
	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
	EffectComponent->DeactivateSystem();
	MovementComponent->StopMovementImmediately();
	SetActorEnableCollision(false);
	GetWorldTimerManager().SetTimer(TeleportTimer, this, &AGWDashProjectile::TeleportTimerElapsed, teleportTime, false);
}
