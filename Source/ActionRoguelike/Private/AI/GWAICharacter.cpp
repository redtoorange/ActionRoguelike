#include "AI/GWAICharacter.h"

#include "DrawDebugHelpers.h"
#include "AI/GWAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

AGWAICharacter::AGWAICharacter()
{
	SensingComponent = CreateDefaultSubobject<UPawnSensingComponent>("SensingComp");
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	AttributeComponent = CreateDefaultSubobject<UGWAttributeComponent>("AttributeComp");
}

void AGWAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SensingComponent->OnSeePawn.AddDynamic(this, &AGWAICharacter::HandlePawnSeen);
	AttributeComponent->OnHealthChange.AddDynamic(this, &AGWAICharacter::HandleHealthChanged);
}

void AGWAICharacter::HandlePawnSeen(APawn* pawn)
{
	AGWAIController* AIC = Cast<AGWAIController>(GetController());
	if (AIC)
	{
		AIC->GetBlackboardComponent()->SetValueAsObject(targetActorKey, pawn);
		DrawDebugString(GetWorld(), GetActorLocation(), "Player Spotted", nullptr, FColor::White, 2.0f, true);
	}
}

void AGWAICharacter::HandleHealthChanged(AActor* HealthChangeInstigator, UGWAttributeComponent* OwningComponent,
                                         float NewHealth, float Delta)
{
	DrawDebugString(GetWorld(), GetActorLocation(), FString::Printf(TEXT("%f"), NewHealth), nullptr, FColor::Red, 2,
	                true);

	if (NewHealth <= 0)
	{
		OnDied();
		OnCharacterDie.Broadcast();
	}
}
