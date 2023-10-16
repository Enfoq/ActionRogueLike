// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectiles/SBaseProjectile.h"

#include "SMagicProjectile.generated.h"

/**
 * 
 */

class UCameraShakeBase;

UCLASS()
class ASMagicProjectile : public ASBaseProjectile
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	virtual void OnProjectileHit (
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit
	) override;

	UPROPERTY(EditDefaultsOnly, Category = "Special Effects")
	TSubclassOf<UCameraShakeBase> CameraShakeEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Special Effects")
	float InnerRadiusOfCameraShake = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Special Effects")
	float OuterRadiusOfCameraShake = 0.0f;
};
