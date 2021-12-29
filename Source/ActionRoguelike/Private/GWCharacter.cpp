#include "GWCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AGWCharacter::AGWCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void AGWCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AGWCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGWCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AGWCharacter::HandleMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGWCharacter::HandleMoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &AGWCharacter::AddControllerYawInput);
}

void AGWCharacter::HandleMoveForward(float axisValue)
{
	AddMovementInput(GetActorForwardVector(), axisValue);
}

void AGWCharacter::HandleMoveRight(float axisValue)
{
	AddMovementInput(GetActorRightVector(), axisValue);
}
