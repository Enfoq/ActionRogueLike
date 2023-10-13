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
class ASBlackHoleProjectile : public ASBaseProjectile
{
	GENERATED_BODY()
	
public:
	ASBlackHoleProjectile();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* RadialForceComp = nullptr;

	UPROPERTY(EditDefaultsOnly)
	float LifeTimeOfProjectile = 5.0f;

	UPROPERTY(EditDefaultsOnly)
	float BlackHoleAnimDelay = 0.4f;

private:
	void DestroyOnTimer();

	UFUNCTION()
	void OnBlackHoleOverlapped(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	void ActivateBlackHole();

	FTimerHandle LifetimeTimerHandle;
};
