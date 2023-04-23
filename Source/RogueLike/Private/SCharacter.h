// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USInteractionComponent;
class UAnimMontage;

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

	UPROPERTY(VisibleAnywhere, Category = Interaction)
	USInteractionComponent* InteractionComp;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;

	FTimerHandle PrimaryAttackTimerHandle;

	void PrimaryAttackTimeElapsed();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Movement */
	void MoveForward(float Value);
	void MoveRight(float Value);

	/** Fire */
	void PrimaryAttack();

	bool bCanFire = true;

	/** Interaction */
	void PrimaryInteract();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void TraceUnderCrosshair();

	FVector_NetQuantize ImpactPoint;
};
