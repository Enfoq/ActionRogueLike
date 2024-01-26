// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckAttackRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

void USBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();
	if (!IsValid(BlackBoardComp))
	{
		return;
	}

	AActor* TargetActor = Cast<AActor>(BlackBoardComp->GetValueAsObject(TEXT("TargetActor")));
	if (!IsValid(TargetActor))
	{
		return;
	}

	AAIController* MyController = OwnerComp.GetAIOwner();
	if (!IsValid(MyController))
	{
		return;
	}

	APawn* AIPawn = MyController->GetPawn();
	if (ensure(AIPawn))
	{
		float DistanceTo = FVector::Distance(TargetActor->GetActorLocation(), AIPawn->GetActorLocation());

		bool bWithingRange = DistanceTo < DistanceThreshold;
		bool bHasLineOfSight = false;

		if (bWithingRange)
		{
			bHasLineOfSight = MyController->LineOfSightTo(TargetActor);
		}

		BlackBoardComp->SetValueAsBool(AttackRangeKey.SelectedKeyName, bWithingRange && bHasLineOfSight);
	}
}
