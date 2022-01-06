#pragma once

#include "CoreMinimal.h"
#include "GWMagicProjectile.h"
#include "GameFramework/Character.h"
#include "GWCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class ACTIONROGUELIKE_API AGWCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AGWCharacter();

protected:
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AGWMagicProjectile> PrimaryAttackClass;

	UPROPERTY(VisibleAnywhere)
	class UGWInteractionComponent* InteractionComponent;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* AttackAnim;

	UPROPERTY(EditAnywhere)
	float projectileDelay = 0.2f;
	
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void HandleMoveForward(float axisValue);
	
	void HandleMoveRight(float axisValue);

	void PrimaryAttack();
	
	void PrimaryAttack_TimerElapsed();

	void PrimaryInteract();
	
	void HandleJump();

	FTimerHandle TimerHandle;
};
