// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SExplosiveBarell.generated.h"

class URadialForceComponent;
class UStaticMeshComponent;

UCLASS()
class ASExplosiveBarell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASExplosiveBarell();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* RadialForceComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComp;

private:
	UFUNCTION()
	void OnBarellHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
