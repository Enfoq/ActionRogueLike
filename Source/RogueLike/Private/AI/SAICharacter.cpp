// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAICharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "AIModule/Classes/AIController.h"
#include "AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Components/SAttributesComponent.h"

ASAICharacter::ASAICharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");
	AttributesComp = CreateDefaultSubobject<USAttributesComponent>(TEXT("Attributes"));
}

void ASAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawnSensingComponent->OnSeePawn.AddDynamic(this, &ThisClass::OnPawnSeen);
	AttributesComp->OnHealthChanged.AddDynamic(this, &ThisClass::OnHealthChanged);
}

void ASAICharacter::OnPawnSeen(APawn* Pawn)
{
	AAIController* AIC = Cast<AAIController>(GetController());

	if (IsValid(AIC))
	{
		UBlackboardComponent* BBComp = AIC->GetBlackboardComponent();

		BBComp->SetValueAsObject(TEXT("TargetActor"), Pawn);
	}
}

void ASAICharacter::OnHealthChanged(AActor* InstigatorActor, USAttributesComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0.0f && IsValid(GetMesh()))
	{
		USkeletalMeshComponent* SkeletalMesh = GetMesh();
		SkeletalMesh->SetScalarParameterValueOnMaterials("HitFlashTime", GetWorld()->GetTimeSeconds());
	}

	if (NewHealth <= 0.0f && Delta < 0.0f)
	{
		Destroy();
	}
}
