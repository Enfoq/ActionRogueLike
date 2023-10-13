// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectiles/SBaseProjectile.h"

#include "SMagicProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ASMagicProjectile : public ASBaseProjectile
{
	GENERATED_BODY()
	
protected:
	virtual void OnProjectileHit (
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit
	) override;
};
