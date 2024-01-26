// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckLowHealth.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Components/SAttributesComponent.h"

void USBTService_CheckLowHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();
	if (!IsValid(BlackBoardComp))
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
		USAttributesComponent* AttrComp = Cast<USAttributesComponent>(AIPawn->GetComponentByClass(USAttributesComponent::StaticClass()));
		if (IsValid(AttrComp))
		{
			bool bLowHealth = AttrComp->IsLowHealth();
			BlackBoardComp->SetValueAsBool(LowHealthKey.SelectedKeyName, bLowHealth);
		}
	}
}
