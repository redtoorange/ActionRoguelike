// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/GWAICharacter.h"

// Sets default values
AGWAICharacter::AGWAICharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGWAICharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGWAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
