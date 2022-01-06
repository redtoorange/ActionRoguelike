#include "GWItemChest.h"

#include "Kismet/GameplayStatics.h"

AGWItemChest::AGWItemChest()
{
	PrimaryActorTick.bCanEverTick = true;

	ChestMesh = CreateDefaultSubobject<UStaticMeshComponent>("ChestMesh");
	SetRootComponent(ChestMesh);

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(ChestMesh);
}

void AGWItemChest::BeginPlay()
{
	Super::BeginPlay();
}

void AGWItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGWItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	IGWGameplayInterface::Interact_Implementation(InstigatorPawn);
	LidMesh->SetRelativeRotation(FRotator(lidOpenValue, 0, 0));
}
