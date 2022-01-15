#include "AI/GWAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

AGWAIController::AGWAIController()
{
}

void AGWAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGWAIController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(BehaviorTree);

	APawn* playerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (ensureAlways(playerPawn))
	{
		GetBlackboardComponent()->SetValueAsObject("TargetActor", playerPawn);
	}
}
