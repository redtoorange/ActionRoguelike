#include "GWInteractionComponent.h"

#include "DrawDebugHelpers.h"
#include "GWCharacter.h"
#include "GWItemChest.h"

UGWInteractionComponent::UGWInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UGWInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UGWInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UGWInteractionComponent::PrimaryInteract()
{
	AGWCharacter* owner = Cast<AGWCharacter>(GetOwner());
	if (owner)
	{
		FVector EyeLocation;
		FRotator EyeRotation;
		// owner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
		owner->GetController()->GetPlayerViewPoint(EyeLocation, EyeRotation);

		FVector Start = EyeLocation;
		FVector End = EyeLocation + (EyeRotation.Vector() * 1000.0f);

		FHitResult HitResult;

		FCollisionObjectQueryParams Params;
		Params.AddObjectTypesToQuery(ECC_WorldDynamic);

		bool blockingHit = GetWorld()->LineTraceSingleByObjectType(HitResult, Start, End, Params);

		AActor* hitActor = HitResult.GetActor();
		if (hitActor)
		{
			IGWGameplayInterface* GameplayInterface = Cast<IGWGameplayInterface>(hitActor);
			if (GameplayInterface)
			{
				APawn* ownerPawn = Cast<APawn>(owner);
				GameplayInterface->Execute_Interact(hitActor, ownerPawn);
			}
		}


		DrawDebugLine(GetWorld(), Start, End, blockingHit ? FColor::Green : FColor::Red, false, 2.0f, 0, 2.0f);


		FCollisionShape Shape;
		Shape.SetSphere(30.0f);

		TArray<FHitResult> HitResults;
		blockingHit = GetWorld()->SweepMultiByObjectType(HitResults, Start, End, FQuat::Identity, Params, Shape);

		for (FHitResult Hit : HitResults)
		{
			AActor* hitActorSphere = HitResult.GetActor();
			if (hitActorSphere)
			{
				if (hitActorSphere->Implements<UGWGameplayInterface>())
				{
					APawn* ownerPawn = Cast<APawn>(owner);
					IGWGameplayInterface::Execute_Interact(hitActorSphere, ownerPawn);
					break;
				}
				// IGWGameplayInterface* GameplayInterface = Cast<IGWGameplayInterface>(hitActorSphere);
				// if (GameplayInterface)
				// {
				// 	APawn* ownerPawn = Cast<APawn>(owner);
				// 	GameplayInterface->Execute_Interact(hitActorSphere, ownerPawn);
				// 	break;
				// }
			}
			// DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 30.0f, 32,  blockingHit ? FColor::Green : FColor::Red, false, 2.0f);
		}
	}
}
