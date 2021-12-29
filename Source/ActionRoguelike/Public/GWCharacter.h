#pragma once

#include "CoreMinimal.h"
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
	
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void HandleMoveForward(float axisValue);
	
	void HandleMoveRight(float axisValue);
};
