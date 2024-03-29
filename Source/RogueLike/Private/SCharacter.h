// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USInteractionComponent;
class UAnimMontage;
class USAttributesComponent;

enum class EAttackType : uint8
{
	SimpleAttack,
	BlackHole,
	Teleport,

	MAX
};

UCLASS()
class ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USAttributesComponent* AttributesComp = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArmComp = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* CameraComp = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Interaction)
	USInteractionComponent* InteractionComp = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	TSubclassOf<AActor> BasicAttackProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	TSubclassOf<AActor> BlackHoleProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	TSubclassOf<AActor> TeleportProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	UAnimMontage* AttackAnim = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	FName HandSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	UParticleSystem* AttachedAttackEffect = nullptr;

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

	UFUNCTION()
	void OnHealthChanged(
		AActor* InstigatorActor,
		USAttributesComponent* OwningComp,
		float NewHealth,
		float Delta
	);

	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void TraceUnderCrosshair();

	void ChangeAttackTypeToTeleport();
	void ChangeAttackTypeToSimple();
	void ChangeAttackTypeToBlackHole();
	FVector GetSocketLocationOnMesh(const FName& SocketName);
	void SpawnAttackAttachedEffect(const FVector& Location, const FRotator& Rotation);

	FVector_NetQuantize ImpactPoint;

	EAttackType AttackType = EAttackType::SimpleAttack;
};
