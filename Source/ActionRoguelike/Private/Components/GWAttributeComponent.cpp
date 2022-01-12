#include "Components/GWAttributeComponent.h"

UGWAttributeComponent::UGWAttributeComponent()
{
	health = 100;
}

bool UGWAttributeComponent::ApplyHealthChange(float delta, AActor* Instigator)
{
	bool success = true;

	health = FMath::Clamp(health + delta, 0.0f, 100.0f);
	OnHealthChange.Broadcast(Instigator, this, health, delta);

	return success;
}
