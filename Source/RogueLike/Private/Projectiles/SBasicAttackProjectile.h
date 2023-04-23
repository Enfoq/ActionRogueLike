// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectiles/SMagicProjectile.h"
#include "SBasicAttackProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ASBasicAttackProjectile : public ASMagicProjectile
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent,
						 AActor* OtherActor, UPrimitiveComponent* OtherComp,
						 FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere)
	UParticleSystem* HitEffect;
};
