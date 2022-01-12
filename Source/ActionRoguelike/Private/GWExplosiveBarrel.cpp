#include "GWExplosiveBarrel.h"

#include "DrawDebugHelpers.h"
#include "PhysicsEngine/RadialForceComponent.h"


// Sets default values
AGWExplosiveBarrel::AGWExplosiveBarrel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	SetRootComponent(StaticMeshComponent);

	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
	RadialForceComponent->SetupAttachment(StaticMeshComponent);

	StaticMeshComponent->SetSimulatePhysics(true);
	StaticMeshComponent->SetCollisionProfileName("PhysicsActor");

	RadialForceComponent->bAutoActivate = false;
	RadialForceComponent->Radius = 600.0f;
	RadialForceComponent->ImpulseStrength = 2000.0f;
	RadialForceComponent->bImpulseVelChange = true;
	RadialForceComponent->bIgnoreOwningActor = true;
}

// Called when the game starts or when spawned
void AGWExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
}

void AGWExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	StaticMeshComponent->OnComponentHit.AddDynamic(this, &AGWExplosiveBarrel::HandleOnHit);
}

// Called every frame
void AGWExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGWExplosiveBarrel::HandleOnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Other Actor: %s at game time %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);
	DrawDebugString(GetWorld(), Hit.ImpactPoint, FString("Test Text"), nullptr, FColor::Green, 2.0f);
	Explode();
}

void AGWExplosiveBarrel::Explode()
{
	RadialForceComponent->FireImpulse();
	Destroy();
}
