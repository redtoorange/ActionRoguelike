#include "GWExplosiveBarrel.h"

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
	Explode();
}

void AGWExplosiveBarrel::Explode()
{
	UE_LOG(LogTemp, Warning, TEXT("HandleOnHit()"));
	RadialForceComponent->FireImpulse();

	Destroy();
}
