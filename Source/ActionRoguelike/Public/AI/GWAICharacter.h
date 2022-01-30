#pragma once

#include "CoreMinimal.h"
#include "Components/GWAttributeComponent.h"
#include "GameFramework/Character.h"
#include "Perception/PawnSensingComponent.h"
#include "GWAICharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterDie);

UCLASS()
class ACTIONROGUELIKE_API AGWAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AGWAICharacter();

	virtual void PostInitializeComponents() override;

	UPROPERTY(BlueprintAssignable)
	FOnCharacterDie OnCharacterDie;

	UFUNCTION(BlueprintImplementableEvent)
	void OnDied();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	FName targetActorKey;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="AI")
	UPawnSensingComponent* SensingComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UGWAttributeComponent* AttributeComponent;

	UFUNCTION()
	void HandlePawnSeen(APawn* pawn);

	UFUNCTION()
	void HandleHealthChanged(AActor* HealthChangeInstigator, UGWAttributeComponent* OwningComponent, float NewHealth,
	                         float Delta);
};
