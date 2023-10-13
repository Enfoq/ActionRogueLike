// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/SMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SAttributesComponent.h"

void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void ASMagicProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!IsValid(OtherActor) || OtherActor == GetInstigator())
	{
		return;
	}

	USAttributesComponent* AttrComp = Cast<USAttributesComponent>(OtherActor->GetComponentByClass(USAttributesComponent::StaticClass()));
	if (IsValid(AttrComp))
	{
		AttrComp->ApplyHealthChange(-20.f);
	}

	Super::OnProjectileHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
}
