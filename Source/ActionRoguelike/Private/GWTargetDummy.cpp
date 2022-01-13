#include "GWTargetDummy.h"
#include "Components/GWAttributeComponent.h"

AGWTargetDummy::AGWTargetDummy()
{
	AttributeComponent = CreateDefaultSubobject<UGWAttributeComponent>("AttributeComponent");

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	SetRootComponent(MeshComponent);
}

void AGWTargetDummy::BeginPlay()
{
	Super::BeginPlay();
	AttributeComponent->OnHealthChange.AddDynamic(this, &AGWTargetDummy::OnHealthChanged);
}

void AGWTargetDummy::OnHealthChanged(AActor* HealthChangeInstigator, UGWAttributeComponent* OwningComponent,
                                     float NewHealth,
                                     float Delta)
{
	if (Delta < 0)
	{
		MeshComponent->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}
}
