#include "Projectiles/GWBaseProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
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
	MovementComponent->InitialSpeed = 1000.0f;
	MovementComponent->bRotationFollowsVelocity = true;
	MovementComponent->bInitialVelocityInLocalSpace = true;
}

void AGWBaseProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComponent->IgnoreActorWhenMoving(GetInstigator(), true);
}

void AGWBaseProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AGWBaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
