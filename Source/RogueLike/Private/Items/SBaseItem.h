// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGameplayInterface.h"
#include "SBaseItem.generated.h"

UCLASS()
class ASBaseItem : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()

public:
	ASBaseItem();

	virtual void Interact_Implementation(APawn* InstigatorPawn);

protected:
	virtual void HideObject();

	UFUNCTION()
	virtual void UnhideObject();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditDefaultsOnly, Category = "ItemOptions")
	float ItemCooldown = 0.0f;

private:
	FTimerHandle ReactivateItemTimerHandle;
	ECollisionEnabled::Type CollisionType;
};
