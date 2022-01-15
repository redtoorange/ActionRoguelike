#include "Powerups/GWPowerUp.h"

#include "Components/GWAttributeComponent.h"

AGWPowerUp::AGWPowerUp()
{
	PrimaryActorTick.bCanEverTick = true;
	
	HealAmount = 10.0f;
	CoolDownLength = 10.0f;
	OnCooldown = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	SetRootComponent(StaticMeshComponent);
}

void AGWPowerUp::BeginPlay()
{
	Super::BeginPlay();
}

void AGWPowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGWPowerUp::Interact_Implementation(APawn* InstigatorPawn)
{
	IGWGameplayInterface::Interact_Implementation(InstigatorPawn);
	ApplyPower(InstigatorPawn);
}

void AGWPowerUp::ApplyPower(APawn* InstigatorPawn)
{
	if(OnCooldown) return;
	
	UGWAttributeComponent* AttributeComponent = InstigatorPawn->FindComponentByClass<UGWAttributeComponent>();
	if(AttributeComponent && !AttributeComponent->IsFullHealth())
	{
		AttributeComponent->ApplyHealthChange(HealAmount, this);
		Hide();
		
		GetWorldTimerManager().SetTimer(CoolDownTimer, this, &AGWPowerUp::Show, CoolDownLength);
	}
}

void AGWPowerUp::Show()
{
	OnCooldown = false;
	StaticMeshComponent->SetVisibility(true);
}

void AGWPowerUp::Hide()
{
	OnCooldown = true;
	StaticMeshComponent->SetVisibility(false);
}
