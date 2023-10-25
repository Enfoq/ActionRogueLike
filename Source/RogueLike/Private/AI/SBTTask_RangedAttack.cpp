// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTask_RangedAttack.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type USBTTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* OwnController = OwnerComp.GetAIOwner();
	if (!IsValid(OwnController))
	{
		return EBTNodeResult::Aborted;
	}

	ACharacter* AIPawn = Cast<ACharacter>(OwnController->GetPawn());

	if (!IsValid(AIPawn))
	{
		return EBTNodeResult::Aborted;
	}

	FVector MuzzleLocation = AIPawn->GetMesh()->GetSocketLocation(TEXT("Muzzle_Front_XForward"));

	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();
	if (!IsValid(BlackBoardComp))
	{
		return EBTNodeResult::Aborted;
	}

	AActor* TargetActor = Cast<AActor>(BlackBoardComp->GetValueAsObject(TEXT("TargetActor")));
	if (!IsValid(TargetActor))
	{
		return EBTNodeResult::Aborted;
	}

	FVector Direction = TargetActor->GetActorLocation() - MuzzleLocation;
	FRotator MuzzleRotation = Direction.Rotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = AIPawn;

	AActor* Projectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);

	if (IsValid(Projectile))
	{
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}
