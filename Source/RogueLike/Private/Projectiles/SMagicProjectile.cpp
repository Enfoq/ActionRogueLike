// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/SMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SAttributesComponent.h"

// Sets default values
ASMagicProjectile::ASMagicProjectile()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComp->SetCollisionProfileName(TEXT("Projectile"));
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnActorOverlap);
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EffectComponent"));
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	MovementComp->InitialSpeed = 1000.f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;

	PrimaryActorTick.bCanEverTick = true;
}

void ASMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValid(OtherActor) || OtherActor == GetInstigator())
	{
		return;
	}

	USAttributesComponent* AttrComp = Cast<USAttributesComponent>(OtherActor->GetComponentByClass(USAttributesComponent::StaticClass()));
	if (IsValid(AttrComp))
	{
		AttrComp->ApplyHealthChange(-20.f);
		Destroy();
	}
}

// Called every frame
void ASMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
