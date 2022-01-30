#include "GWCharacter.h"

#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GWInteractionComponent.h"
#include "Components/GWAttributeComponent.h"
#include "Projectiles/GWBaseProjectile.h"

#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

AGWCharacter::AGWCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	InteractionComponent = CreateDefaultSubobject<UGWInteractionComponent>("InteractionComponent");
	AttributeComponent = CreateDefaultSubobject<UGWAttributeComponent>("AttributeComponent");

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
	muzzleName = "Muzzle_01";
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
	PlayerInputComponent->BindAction("BlackHoleAttack", IE_Pressed, this, &AGWCharacter::BlackHoleAttack);
	PlayerInputComponent->BindAction("TeleportAttack", IE_Pressed, this, &AGWCharacter::TeleportAttack);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AGWCharacter::HandleJump);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &AGWCharacter::PrimaryInteract);
}

void AGWCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AttributeComponent->OnHealthChange.AddDynamic(this, &AGWCharacter::OnHealthChanged);
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
	if (!AttackTimer.IsValid())
	{
		PlayAnimMontage(AttackAnim);
		GetWorldTimerManager().SetTimer(AttackTimer, this, &AGWCharacter::PrimaryAttack_TimerElapsed, projectileDelay);
	}
}

void AGWCharacter::BlackHoleAttack()
{
	if (!AttackTimer.IsValid())
	{
		PlayAnimMontage(AttackAnim);
		GetWorldTimerManager().SetTimer(AttackTimer, this, &AGWCharacter::BlackHoleAttack_TimerElapsed, blackHoleDelay);
	}
}

void AGWCharacter::TeleportAttack()
{
	if (!AttackTimer.IsValid())
	{
		PlayAnimMontage(AttackAnim);
		GetWorldTimerManager().SetTimer(AttackTimer, this, &AGWCharacter::TeleportAttack_TimerElapsed, teleportDelay);
	}
}

void AGWCharacter::HandleJump()
{
	Jump();
}

void AGWCharacter::PrimaryInteract()
{
	InteractionComponent->PrimaryInteract();
}

FVector AGWCharacter::GetTargetEndPoint()
{
	FVector viewPosition;
	FRotator viewRotation;
	GetController()->GetPlayerViewPoint(viewPosition, viewRotation);

	const FVector endPoint = viewPosition + viewRotation.Vector() * 10000;
	FHitResult HitResult;

	FCollisionShape shape;
	shape.SetSphere(20.0f);
	
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);
	
	if (GetWorld()->SweepSingleByObjectType(HitResult, viewPosition, endPoint, FQuat::Identity, ObjectQueryParams, shape, Params))
	{
		return HitResult.ImpactPoint;
	}

	return endPoint;
}

void AGWCharacter::PrimaryAttack_TimerElapsed()
{
	SpawnAttack(PrimaryAttackClass);
}



void AGWCharacter::BlackHoleAttack_TimerElapsed()
{
	SpawnAttack(BlackHoleAttackClass);
}

void AGWCharacter::SpawnAttack(TSubclassOf<AGWBaseProjectile> attack)
{
	if (ensureAlways(attack))
	{
		UGameplayStatics::SpawnEmitterAttached(CastingVFX, GetMesh(), muzzleName);

		FVector HandLocation = GetMesh()->GetSocketLocation(muzzleName);
		FVector direction = GetTargetEndPoint() - HandLocation;
		FRotator lookRotation = FRotationMatrix::MakeFromX(direction).Rotator();

		FTransform SpawnTM = FTransform(lookRotation, HandLocation);

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParameters.Instigator = this;

		AGWBaseProjectile* projectile = GetWorld()->SpawnActor<AGWBaseProjectile>(attack, SpawnTM, SpawnParameters);
		AttackTimer.Invalidate();
	}
}



void AGWCharacter::TeleportAttack_TimerElapsed()
{
	SpawnAttack(TeleportAttackClass);
}

void AGWCharacter::OnHealthChanged(AActor* HealthChangeInstigator, UGWAttributeComponent* OwningComponent,
	float NewHealth, float Delta)
{
	if(Delta < 0)
	{
		GetMesh()->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}
	
	if(NewHealth <= 0 && Delta < 0)
	{
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		DisableInput(PlayerController);
	}
}
