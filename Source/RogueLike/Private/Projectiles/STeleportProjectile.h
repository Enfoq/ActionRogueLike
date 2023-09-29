// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectiles/SMagicProjectile.h"
#include "STeleportProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ASTeleportProjectile : public ASBaseProjectile
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	float DetonateTimerValue = 0.3f;

	UPROPERTY(EditDefaultsOnly)
	float TimeToTeleport = 0.3f;

protected:
	virtual void BeginPlay() override;
	
	virtual void OnProjectileHit(
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit
	) override;

	virtual void Explode_Implementation() override;

private:
	void Detonate();
	void Teleport();

	UFUNCTION()
	void StartDetonateTimer();
	void StopDetonateTimer();

	UFUNCTION()
	void StartTeleportTimer();

	FTimerHandle DetonateTimerHandle;
	FTimerHandle TeleportTimerHandle;
};
