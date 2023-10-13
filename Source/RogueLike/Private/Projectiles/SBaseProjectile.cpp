// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/SBaseProjectile.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

// Sets default values
ASBaseProjectile::ASBaseProjectile()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EffectComponent"));
	EffectComp->SetupAttachment(SphereComp);

	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	MovementComp->InitialSpeed = 1000.f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;

	PrimaryActorTick.bCanEverTick = true;
}

void ASBaseProjectile::BeginPlay()
{
	Super::BeginPlay();

	SphereComp->OnComponentHit.AddDynamic(this, &ThisClass::OnProjectileHit);
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);

	AudioComp->Play();
}

void ASBaseProjectile::OnProjectileHit(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, 
	const FHitResult& Hit
)
{
	Explode();
}

void ASBaseProjectile::Explode_Implementation()
{
	if (IsValid(this))
	{
		SpawnProjectileHitEffects();
		Destroy();
	}
}

void ASBaseProjectile::SpawnProjectileHitEffects_Implementation()
{
	if (HitEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, GetActorLocation(), GetActorRotation());
	}

	if (SoundHitEffect)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundHitEffect, GetActorLocation());
	}
}
