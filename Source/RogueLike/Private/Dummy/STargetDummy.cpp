// Fill out your copyright notice in the Description page of Project Settings.


#include "Dummy/STargetDummy.h"
#include "Components/SAttributesComponent.h"

ASTargetDummy::ASTargetDummy()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	AttributeComponent = CreateDefaultSubobject<USAttributesComponent>("AttributeComp");
}

void ASTargetDummy::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(AttributeComponent))
	{
		AttributeComponent->OnHealthChanged.AddDynamic(this, &ThisClass::OnHealthChanged);
	}
}

void ASTargetDummy::OnHealthChanged(AActor* InstigatorActor, USAttributesComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0.0f)
	{
		MeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->GetTimeSeconds());
	}
}
