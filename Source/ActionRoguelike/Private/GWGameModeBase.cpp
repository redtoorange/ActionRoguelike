#include "GWGameModeBase.h"

#include "EngineUtils.h"
#include "AI/GWAICharacter.h"
#include "Components/GWAttributeComponent.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "GameFramework/Character.h"

AGWGameModeBase::AGWGameModeBase()
{
	SpawnTimerInterval = 2.0f;
}

void AGWGameModeBase::StartPlay()
{
	Super::StartPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &AGWGameModeBase::SpawnBotTimerElapsed,
	                                SpawnTimerInterval, true);
}

void AGWGameModeBase::SpawnBotTimerElapsed()
{
	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(
		GetWorld(), SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);

	if (ensure(QueryInstance))
	{
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &AGWGameModeBase::OnQueryCompleted);
	}
}

void AGWGameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* Wrapper, EEnvQueryStatus::Type Status)
{
	if (Status == EEnvQueryStatus::Type::Success)
	{
		int32 NumberOfBots = 0;
		for (TActorIterator<AGWAICharacter> It(GetWorld()); It; ++It)
		{
			AGWAICharacter* Bot = *It;
			UGWAttributeComponent* Attribute = Bot->FindComponentByClass<UGWAttributeComponent>();

			if (Attribute && Attribute->IsAlive())
			{
				NumberOfBots++;
			}
		}

		float maxBots = 10;
		if (DifficultyCurve)
		{
			maxBots = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
		}
		if (NumberOfBots >= maxBots)
		{
			return;
		}


		TArray<FVector> Locations = Wrapper->GetResultsAsLocations();
		if (Locations.Num() > 0)
		{
			GetWorld()->SpawnActor<ACharacter>(MinionClass, Locations[0], FRotator::ZeroRotator);
		}
	}
}
