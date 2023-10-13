// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/SBlackHoleProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

ASBlackHoleProjectile::ASBlackHoleProjectile()
{
	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComponent"));
	RadialForceComp->SetupAttachment(RootComponent);
}

void ASBlackHoleProjectile::BeginPlay()
{
	Super::BeginPlay();

	SphereComp->OnComponentHit.Clear();
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);

	RadialForceComp->bAutoActivate = false;

	FTimerHandle ActivateBlackHoleTHandle;
	GetWorldTimerManager().SetTimer(ActivateBlackHoleTHandle, this, &ThisClass::ActivateBlackHole, 0.1f, false, BlackHoleAnimDelay);

	if (LifeTimeOfProjectile < BlackHoleAnimDelay)
	{
		LifeTimeOfProjectile *= 2.f; //double the value of lifetime if it's < than anim delay
	}
	GetWorldTimerManager().SetTimer(LifetimeTimerHandle, this, &ThisClass::DestroyOnTimer, 0.1f, false, LifeTimeOfProjectile);
}

void ASBlackHoleProjectile::DestroyOnTimer()
{
	Destroy();
}

void ASBlackHoleProjectile::OnBlackHoleOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValid(OtherActor) || !IsValid(OtherComp))
	{
		return;
	}

	if (OtherComp->IsSimulatingPhysics())
	{
		OtherActor->Destroy();
	}
}

void ASBlackHoleProjectile::ActivateBlackHole()
{
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBlackHoleOverlapped);
	SphereComp->SetGenerateOverlapEvents(true);
	MovementComp->MaxSpeed = 300.f;

	RadialForceComp->Activate();
}
