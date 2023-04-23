// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/SBlackHoleProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

#define BLACKHOLE_ANIM_DELAY 0.5f

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

	GetWorldTimerManager().SetTimer(LifetimeTimerHandle, this, &ThisClass::DestroyOnTimer, 5.0f, false, 5.0f);
	GetWorldTimerManager().SetTimer(ForceApplyTimerHandle, this, &ThisClass::DestroyOverlappedActors, 0.1f, true, BLACKHOLE_ANIM_DELAY);
}

void ASBlackHoleProjectile::DestroyOnTimer()
{
	GetWorldTimerManager().ClearTimer(ForceApplyTimerHandle);
	Destroy();
}

void ASBlackHoleProjectile::DestroyOverlappedActors()
{
	TArray<AActor*> OverlappingActors;
	SphereComp->GetOverlappingActors(OverlappingActors);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("There are %d overlapped actors"), OverlappingActors.Num()));
	for (AActor* OverActor : OverlappingActors)
	{
		OverActor->Destroy();
	}
}
