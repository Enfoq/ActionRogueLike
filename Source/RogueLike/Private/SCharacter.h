// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* CameraComp;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> PrimaryAttackProjectileClass;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Movement */
	void MoveForward(float Value);
	void MoveRight(float Value);

	/** Fire */
	void PrimaryAttack();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
