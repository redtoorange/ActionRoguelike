// Fill out your copyright notice in the Description page of Project Settings.


#include "GWMagicProjectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AGWMagicProjectile::AGWMagicProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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

// Called when the game starts or when spawned
void AGWMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGWMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
