// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveObjects/SExplosiveBarell.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interfaces/SProjectileInterface.h"

// Sets default values
ASExplosiveBarell::ASExplosiveBarell()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComp;

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComponent"));
	RadialForceComp->SetupAttachment(StaticMeshComp);
}

// Called when the game starts or when spawned
void ASExplosiveBarell::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		StaticMeshComp->OnComponentHit.AddDynamic(this, &ThisClass::OnBarellHit);
	}
}

void ASExplosiveBarell::OnBarellHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (UKismetSystemLibrary::DoesImplementInterface(OtherActor, USProjectileInterface::StaticClass()))
	{
		RadialForceComp->FireImpulse();
	}
}

// Called every frame
void ASExplosiveBarell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
