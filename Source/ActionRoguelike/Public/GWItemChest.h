// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GWGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "GWItemChest.generated.h"

class UStaticMeshComponent;

UCLASS()
class ACTIONROGUELIKE_API AGWItemChest : public AActor, public IGWGameplayInterface
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ChestMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LidMesh;

	UPROPERTY(EditAnywhere)
	float lidOpenValue = 110.0f;
public:
	void Interact_Implementation(APawn* InstigatorPawn) override;
	
	virtual void Tick(float DeltaTime) override;

	
	AGWItemChest();
};
