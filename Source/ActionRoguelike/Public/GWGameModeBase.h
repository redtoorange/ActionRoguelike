#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "GameFramework/GameModeBase.h"
#include "GWGameModeBase.generated.h"


UCLASS()
class ACTIONROGUELIKE_API AGWGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGWGameModeBase();

	virtual void StartPlay() override;

private:
	FTimerHandle TimerHandle_SpawnBots;


protected:
	UFUNCTION()
	void OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* EnvQueryInstanceBlueprintWrapper,
	                      EEnvQueryStatus::Type Arg);

	UFUNCTION()
	void SpawnBotTimerElapsed();

	UPROPERTY(EditAnywhere, Category="AI")
	float SpawnTimerInterval;

	UPROPERTY(EditAnywhere, Category="AI")
	UEnvQuery* SpawnBotQuery;

	UPROPERTY(EditAnywhere, Category="AI")
	TSubclassOf<ACharacter> MinionClass;

	UPROPERTY(EditAnywhere, Category="AI")
	UCurveFloat* DifficultyCurve;
};
