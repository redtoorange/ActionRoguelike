#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GWAIController.generated.h"

/**
 * This will be acting as the brains of the AI Character
 */
UCLASS()
class ACTIONROGUELIKE_API AGWAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category="AI")
	UBehaviorTree* BehaviorTree;

public:
	AGWAIController();
	
	virtual void Tick(float DeltaTime) override;
};
