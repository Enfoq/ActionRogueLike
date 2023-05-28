// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectiles/SMagicProjectile.h"
#include "STeleportProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ASTeleportProjectile : public ASMagicProjectile
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	float DetonateTimerValue = 0.3f;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent,
						 AActor* OtherActor, UPrimitiveComponent* OtherComp,
						 FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere)
	UParticleSystem* HitEffect;

private:
	void Detonate();
	void Teleport();

	UFUNCTION()
	void StartDetonateTimer();

	UFUNCTION()
	void StartTeleportTimer();
};
