#include "AI/GWAICharacter.h"

#include "DrawDebugHelpers.h"
#include "AI/GWAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

AGWAICharacter::AGWAICharacter()
{
	SensingComponent = CreateDefaultSubobject<UPawnSensingComponent>("SensingComp");
}

void AGWAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SensingComponent->OnSeePawn.AddDynamic(this, &AGWAICharacter::HandlePawnSeen);
}

void AGWAICharacter::HandlePawnSeen(APawn* pawn)
{
	AGWAIController* AIC = Cast<AGWAIController>(GetController());
	if(AIC)
	{
		AIC->GetBlackboardComponent()->SetValueAsObject(targetActorKey, pawn);
		DrawDebugString(GetWorld(), GetActorLocation(), "Player Spotted", nullptr, FColor::White, 2.0f, true);
	}
}
