// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectiles/SMagicProjectile.h"
#include "SBlackHoleProjectile.generated.h"

class URadialForceComponent;

/**
 * 
 */
UCLASS()
class ASBlackHoleProjectile : public ASMagicProjectile
{
	GENERATED_BODY()
	
public:
	ASBlackHoleProjectile();

	void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* RadialForceComp;

	UPROPERTY(EditDefaultsOnly)
	float LifeTimeOfProjectile = 5.0f;

private:
	void DestroyOnTimer();

	void DestroyOverlappedActors();

	void ActivateBlackHole();

	FTimerHandle LifetimeTimerHandle;

	FTimerHandle PullInOverlappedActorsTimerHandle;
};
