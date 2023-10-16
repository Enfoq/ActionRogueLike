// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/SHealthPotionItem.h"
#include "Components/SAttributesComponent.h"

void ASHealthPotionItem::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!IsValid(InstigatorPawn))
	{
		return;
	}

	USAttributesComponent* AttributeComponent = Cast<USAttributesComponent>(InstigatorPawn->GetComponentByClass(USAttributesComponent::StaticClass()));
	if (IsValid(AttributeComponent))
	{
		if (AttributeComponent->IsHealthFull())
		{
			return;
		}

		AttributeComponent->ApplyHealthChange(HealValue);
	}

	Super::Interact_Implementation(InstigatorPawn);
}
