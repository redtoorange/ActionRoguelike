// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/GWBTService_CheckAttackRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UGWBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// Check distance between AI Actor and Target Actor

	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();
	if (ensure(BlackBoardComp))
	{
		AActor* TargetActor = Cast<AActor>(BlackBoardComp->GetValueAsObject(TargetActorKey.SelectedKeyName));
		if (TargetActor)
		{
			AAIController* OwningController = OwnerComp.GetAIOwner();
			if (ensure(OwningController))
			{
				APawn* AIPawn = OwningController->GetPawn();
				if (ensure(AIPawn))
				{
					float Distance = FVector::Distance(AIPawn->GetActorLocation(), TargetActor->GetActorLocation());
					bool bWithinRange = Distance < 2000.0f;
					
					bool bHasLOS = false;
					if(bWithinRange)
					{
						bHasLOS = OwningController->LineOfSightTo(TargetActor);
					}
					
					BlackBoardComp->SetValueAsBool(AttackRangeKey.SelectedKeyName, bWithinRange && bHasLOS);
				}
			}
		}
	}
}
