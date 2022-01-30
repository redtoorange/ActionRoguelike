#include "Components/GWAttributeComponent.h"

UGWAttributeComponent::UGWAttributeComponent()
{
	Health = 100;
	MaxHealth = 100;
}

void UGWAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
}

bool UGWAttributeComponent::ApplyHealthChange(float delta, AActor* Instigator)
{
	bool success = true;

	float oldHealth = Health;
	Health = FMath::Clamp(Health + delta, 0.0f, MaxHealth);
	OnHealthChange.Broadcast(Instigator, this, Health, Health - oldHealth);

	return success;
}

bool UGWAttributeComponent::IsAlive() const
{
	return Health > 0;
}

bool UGWAttributeComponent::IsFullHealth() const
{
	return Health == MaxHealth;
}

float UGWAttributeComponent::GetMaxHealth() const
{
	return MaxHealth;
}
