// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/SBaseItem.h"
#include "SHealthPotionItem.generated.h"

/**
 * 
 */
UCLASS()
class ASHealthPotionItem : public ASBaseItem
{
	GENERATED_BODY()

public:
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ItemOptions")
	float HealValue = 0.0f;
};
