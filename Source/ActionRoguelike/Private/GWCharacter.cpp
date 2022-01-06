#include "GWCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GWInteractionComponent.h"

#include "GameFramework/SpringArmComponent.h"

AGWCharacter::AGWCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	InteractionComponent = CreateDefaultSubobject<UGWInteractionComponent>("InteractionComponent");

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
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

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &AGWCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AGWCharacter::HandleJump);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &AGWCharacter::PrimaryInteract);
}

void AGWCharacter::HandleMoveForward(float axisValue)
{
	FRotator controlRot = GetControlRotation();
	controlRot.Pitch = 0;
	controlRot.Roll = 0;
	AddMovementInput(controlRot.Vector(), axisValue);
}

void AGWCharacter::HandleMoveRight(float axisValue)
{
	FRotator controlRot = GetControlRotation();
	controlRot.Pitch = 0;
	controlRot.Roll = 0;

	FVector rightVector = FRotationMatrix(controlRot).GetScaledAxis(EAxis::Y);

	AddMovementInput(rightVector, axisValue);
}

void AGWCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AGWCharacter::PrimaryAttack_TimerElapsed, projectileDelay);
}

void AGWCharacter::HandleJump()
{
	Jump();
}

void AGWCharacter::PrimaryInteract()
{
	InteractionComponent->PrimaryInteract();
}

void AGWCharacter::PrimaryAttack_TimerElapsed()
{
	FVector muzzleLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	FTransform SpawnTM = FTransform(GetControlRotation(), muzzleLocation);
	
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	AGWMagicProjectile* projectile = GetWorld()->SpawnActor<AGWMagicProjectile>(PrimaryAttackClass, SpawnTM, SpawnParameters);
}
