// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/SBaseItem.h"

void ASBaseItem::Interact_Implementation(APawn* InstigatorPawn)
{
	HideObject();

	UWorld* World = GetWorld();
	if (IsValid(World))
	{
		World->GetTimerManager().SetTimer(ReactivateItemTimerHandle, this, &ASBaseItem::UnhideObject, ItemCooldown, false, ItemCooldown);
	}
}

ASBaseItem::ASBaseItem()
{
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = ItemMesh;
}

void ASBaseItem::HideObject()
{
	ItemMesh->SetVisibility(false, true);
	CollisionType = ItemMesh->GetCollisionEnabled();
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ASBaseItem::UnhideObject()
{
	ItemMesh->SetVisibility(true, true);
	ItemMesh->SetCollisionEnabled(CollisionType);
}
