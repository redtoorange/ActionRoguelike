#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "GameFramework/Character.h"
#include "Perception/PawnSensingComponent.h"
#include "GWAICharacter.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AGWAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AGWAICharacter();
	virtual void PostInitializeComponents() override;
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	FName targetActorKey;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="AI")
	UPawnSensingComponent* SensingComponent;

	UFUNCTION()
	void HandlePawnSeen(APawn* pawn);
};
