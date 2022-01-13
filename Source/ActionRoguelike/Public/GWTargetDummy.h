// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GWTargetDummy.generated.h"


class UGWAttributeComponent;
UCLASS()
class ACTIONROGUELIKE_API AGWTargetDummy : public AActor
{
	GENERATED_BODY()

public:
	AGWTargetDummy();

protected:
	UFUNCTION()
	void OnHealthChanged(AActor* HealthChangeInstigator, UGWAttributeComponent* OwningComponent, float NewHealth, float Delta);

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UGWAttributeComponent* AttributeComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;
};
