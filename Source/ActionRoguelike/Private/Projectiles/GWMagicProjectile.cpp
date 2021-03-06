#include "Projectiles/GWMagicProjectile.h"

#include "DrawDebugHelpers.h"
#include "Components/GWAttributeComponent.h"
#include "Components/SphereComponent.h"


AGWMagicProjectile::AGWMagicProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGWMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AGWMagicProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AGWMagicProjectile::OnActorOverlap);
}

void AGWMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGWMagicProjectile::OnActorOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* Actor,
                                        UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg,
                                        const FHitResult& HitResult)
{
	if (Actor && Actor != GetInstigator())
	{
		UGWAttributeComponent* AttributeComponent = Actor->FindComponentByClass<UGWAttributeComponent>();
		if (AttributeComponent)
		{
			AttributeComponent->ApplyHealthChange(-5.0f, this);
			Explode();
		}
	}
}
