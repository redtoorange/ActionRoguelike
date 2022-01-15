#pragma once

#include "CoreMinimal.h"
#include "GWGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "GWPowerUp.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AGWPowerUp : public AActor, public IGWGameplayInterface
{
	GENERATED_BODY()
	
public:	
	AGWPowerUp();
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

protected:
	virtual void BeginPlay() override;

	virtual void ApplyPower(APawn* InstigatorPawn);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Powerup")
	float HealAmount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Powerup")
	float CoolDownLength;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	FTimerHandle CoolDownTimer;

	UFUNCTION()
	void Show();

private:
	void Hide();

	bool OnCooldown;
};
