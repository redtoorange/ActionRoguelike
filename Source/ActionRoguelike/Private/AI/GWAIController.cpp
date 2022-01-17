#include "AI/GWAIController.h"

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

	if (ensureMsgf(BehaviorTree, TEXT("Behavior Tree is null! Please assign BehaviorTree in your AIController")))
	{
		RunBehaviorTree(BehaviorTree);
	}
	//
	// APawn* playerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	// if (ensureAlways(playerPawn))
	// {
	// 	GetBlackboardComponent()->SetValueAsObject("TargetActor", playerPawn);
	// }
}
