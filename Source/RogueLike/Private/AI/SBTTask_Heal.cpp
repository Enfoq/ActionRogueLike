// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTask_Heal.h"
#include "AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "AIModule/Classes/AIController.h"
#include "GameFramework/Pawn.h"
#include "Components/SAttributesComponent.h"

EBTNodeResult::Type USBTTask_Heal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();
	if (!IsValid(BlackBoardComp))
	{
		return EBTNodeResult::Aborted;
	}

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!IsValid(AIController))
	{
		return EBTNodeResult::Aborted;
	}

	APawn* AIPawn = AIController->GetPawn();
	if (ensure(AIPawn))
	{
		USAttributesComponent* AttrComp = Cast<USAttributesComponent>(AIPawn->GetComponentByClass(USAttributesComponent::StaticClass()));
		if (IsValid(AttrComp))
		{
			AttrComp->ApplyHealthChange(HealValue);

			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
