// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/SBasicAttackProjectile.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

void ASBasicAttackProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->OnComponentHit.AddDynamic(this, &ThisClass::OnProjectileHit);
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
}

void ASBasicAttackProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, GetActorLocation(), GetActorRotation());
	Destroy();
}
