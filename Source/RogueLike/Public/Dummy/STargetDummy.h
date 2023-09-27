// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "STargetDummy.generated.h"

class USAttributesComponent;

UCLASS()
class ROGUELIKE_API ASTargetDummy : public AActor
{
	GENERATED_BODY()
	
public:
	ASTargetDummy();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USAttributesComponent* AttributeComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributesComponent* OwningComp, float NewHealth, float Delta);
};
