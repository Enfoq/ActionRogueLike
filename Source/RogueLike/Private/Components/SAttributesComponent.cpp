// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SAttributesComponent.h"

bool USAttributesComponent::ApplyHealthChange(float Delta)
{
	Health = FMath::Clamp(Health + Delta, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);
	return true;
}

bool USAttributesComponent::IsHealthFull() const
{
	return Health == MaxHealth;
}

bool USAttributesComponent::IsAlive() const
{
	return Health > 0.0f;
}
