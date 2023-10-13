// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/STeleportProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"

void ASTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();

	StartDetonateTimer();
}

void ASTeleportProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	StopDetonateTimer();
	Detonate();
}

void ASTeleportProjectile::Explode_Implementation()
{
	SpawnProjectileHitEffects();
	StartTeleportTimer();
}

void ASTeleportProjectile::Detonate()
{
	MovementComp->StopMovementImmediately();
	SphereComp->SetSimulatePhysics(false);
	SetActorEnableCollision(false);

	Explode();
}

void ASTeleportProjectile::Teleport()
{
	APawn* InstigatorPawn = GetInstigator();
	if (IsValid(InstigatorPawn))
	{
		InstigatorPawn->TeleportTo(GetActorLocation(), InstigatorPawn->GetActorRotation(), false, true);
	}
	
	Destroy();
}

void ASTeleportProjectile::StartDetonateTimer()
{
	GetWorldTimerManager().SetTimer(DetonateTimerHandle, this, &ThisClass::Detonate, DetonateTimerValue, false, DetonateTimerValue);
}

void ASTeleportProjectile::StopDetonateTimer()
{
	GetWorldTimerManager().ClearTimer(DetonateTimerHandle);
}

void ASTeleportProjectile::StartTeleportTimer()
{
	GetWorldTimerManager().SetTimer(TeleportTimerHandle, this, &ThisClass::Teleport, TimeToTeleport, false, TimeToTeleport);
}
