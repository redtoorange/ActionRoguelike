#include "Projectiles/GWMagicProjectile.h"

#include "Components/GWAttributeComponent.h"
#include "Components/SphereComponent.h"


AGWMagicProjectile::AGWMagicProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGWMagicProjectile::BeginPlay()
{
	Super::BeginPlay();

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
	if (Actor)
	{
		UGWAttributeComponent* AttributeComponent = Actor->FindComponentByClass<UGWAttributeComponent>();
		if (AttributeComponent)
		{
			AttributeComponent->ApplyHealthChange(-20.0f, this);
			Destroy();
		}
	}
}
