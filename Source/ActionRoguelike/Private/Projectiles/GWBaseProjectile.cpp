#include "Projectiles/GWBaseProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


AGWBaseProjectile::AGWBaseProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComponent->SetCollisionProfileName("Projectile");
	RootComponent = SphereComponent;

	EffectComponent = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComponent->SetupAttachment(SphereComponent);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComponent->InitialSpeed = 8000.0f;
	MovementComponent->bRotationFollowsVelocity = true;
	MovementComponent->bInitialVelocityInLocalSpace = true;
	MovementComponent->ProjectileGravityScale = 0.0f;
}

void AGWBaseProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	// SphereComponent->IgnoreActorWhenMoving(GetInstigator(), true);
	SphereComponent->OnComponentHit.AddDynamic(this, &AGWBaseProjectile::OnActorHit);
}

void AGWBaseProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AGWBaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGWBaseProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Explode();
}

void AGWBaseProjectile::Explode_Implementation()
{
	if (ensure(!IsPendingKill()))
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
		Destroy();
	}
}
