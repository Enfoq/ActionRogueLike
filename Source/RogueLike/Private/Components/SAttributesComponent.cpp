// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SAttributesComponent.h"

USAttributesComponent::USAttributesComponent()
{
	Health = 100.f;
}

bool USAttributesComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;
	return true;
}
