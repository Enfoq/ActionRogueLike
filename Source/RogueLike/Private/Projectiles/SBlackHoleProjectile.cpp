// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/SBlackHoleProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

#define BLACKHOLE_ANIM_DELAY 0.4f

ASBlackHoleProjectile::ASBlackHoleProjectile()
{
	SphereComp->SetCollisionProfileName(TEXT("BlackHoleProjectile"));
	SphereComp->SetGenerateOverlapEvents(true);

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComponent"));
	EObjectTypeQuery ObjectType = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn);
	RadialForceComp->RemoveObjectTypeToAffect(ObjectType);
	RadialForceComp->SetupAttachment(RootComponent);
}

void ASBlackHoleProjectile::BeginPlay()
{
	Super::BeginPlay();
	RadialForceComp->bAutoActivate = false;
	
	GetWorldTimerManager().SetTimer(LifetimeTimerHandle, this, &ThisClass::DestroyOnTimer, 0.1f, false, LifeTimeOfProjectile);
	GetWorldTimerManager().SetTimer(PullInOverlappedActorsTimerHandle, this, &ThisClass::DestroyOverlappedActors, 0.1f, true, BLACKHOLE_ANIM_DELAY);

	FTimerHandle ActivateBlackHoleTHandle;
	GetWorldTimerManager().SetTimer(ActivateBlackHoleTHandle, this, &ThisClass::ActivateBlackHole, 0.1f, false, BLACKHOLE_ANIM_DELAY);
}

void ASBlackHoleProjectile::DestroyOnTimer()
{
	GetWorldTimerManager().ClearTimer(PullInOverlappedActorsTimerHandle);
	Destroy();
}

void ASBlackHoleProjectile::DestroyOverlappedActors()
{
	TArray<AActor*> OverlappingActors;
	SphereComp->GetOverlappingActors(OverlappingActors);
	for (AActor* OverActor : OverlappingActors)
	{
		OverActor->Destroy();
	}
}

void ASBlackHoleProjectile::ActivateBlackHole()
{
	MovementComp->MaxSpeed = 300.f;
	RadialForceComp->Activate();
}
