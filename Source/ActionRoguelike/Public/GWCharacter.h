#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GWCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class AGWBaseProjectile;

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

	UPROPERTY(EditAnywhere, Category="Attacks")
	TSubclassOf<AGWBaseProjectile> PrimaryAttackClass;

	UPROPERTY(EditAnywhere, Category="Attacks")
	TSubclassOf<AGWBaseProjectile> BlackHoleAttackClass;

	UPROPERTY(EditAnywhere, Category="Attacks")
	TSubclassOf<AGWBaseProjectile> TeleportAttackClass;
	
	UPROPERTY(VisibleAnywhere)
	class UGWInteractionComponent* InteractionComponent;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* AttackAnim;

	UPROPERTY(EditAnywhere)
	float projectileDelay = 0.2f;

	UPROPERTY(EditAnywhere)
	float blackHoleDelay = 0.2f;

	UPROPERTY(EditAnywhere)
	float teleportDelay = 0.2f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UGWAttributeComponent* AttributeComponent;
		
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void HandleMoveForward(float axisValue);
	
	void HandleMoveRight(float axisValue);

	void PrimaryAttack();
	void PrimaryAttack_TimerElapsed();

	void BlackHoleAttack();
	void BlackHoleAttack_TimerElapsed();

	void TeleportAttack();
	void TeleportAttack_TimerElapsed();

	void PrimaryInteract();
	
	void HandleJump();

	FTimerHandle AttackTimer;

	FVector GetTargetEndPoint();

	void SpawnAttack(TSubclassOf<AGWBaseProjectile> attack);
};
