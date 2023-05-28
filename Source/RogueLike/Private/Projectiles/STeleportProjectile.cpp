// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/STeleportProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"

void ASTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();

	SphereComp->OnComponentHit.AddDynamic(this, &ThisClass::OnProjectileHit);
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
	StartDetonateTimer();
}

void ASTeleportProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Detonate();
}

void ASTeleportProjectile::Detonate()
{
	MovementComp->StopMovementImmediately();
	if (HitEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, GetActorLocation(), GetActorRotation());
	}
	StartTeleportTimer();
}

void ASTeleportProjectile::Teleport()
{
	APawn* InstigatorPawn = GetInstigator();
	if (InstigatorPawn)
	{
		InstigatorPawn->TeleportTo(GetActorLocation(), InstigatorPawn->GetActorRotation(), false, true);
	}
	Destroy();
}

void ASTeleportProjectile::StartDetonateTimer()
{
	FTimerHandle DetonateTimerHandle;
	GetWorldTimerManager().SetTimer(DetonateTimerHandle, this, &ThisClass::Detonate, DetonateTimerValue, false);
}

void ASTeleportProjectile::StartTeleportTimer()
{
	FTimerHandle TeleportTimerHandle;
	GetWorldTimerManager().SetTimer(TeleportTimerHandle, this, &ThisClass::Teleport, DetonateTimerValue, false);
}
