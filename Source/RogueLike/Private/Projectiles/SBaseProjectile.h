// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/SProjectileInterface.h"

#include "SBaseProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;
class UParticleSystem;

UCLASS()
class ASBaseProjectile : public AActor, public ISProjectileInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASBaseProjectile();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* EffectComp;

	UFUNCTION()
	virtual void OnProjectileHit(
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit
	);

	UFUNCTION(BlueprintNativeEvent)
	void Explode();

	virtual void Explode_Implementation();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	UParticleSystem* HitEffect;
};
