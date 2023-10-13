// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InteractionComponents/SInteractionComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SAttributesComponent.h"

#define TRACE_LENGTH 5000.f;

DEFINE_LOG_CATEGORY_STATIC(PLAYER, All, All)

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->SetUsingAbsoluteRotation(true);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<USInteractionComponent>(TEXT("Interaction"));

	AttributesComp = CreateDefaultSubobject<USAttributesComponent>(TEXT("Attributes"));

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
}

void ASCharacter::PrimaryAttackTimeElapsed()
{
	FVector HandLocation = GetMesh()->GetSocketLocation(TEXT("Muzzle_01"));
	FRotator SpawnRotation = UKismetMathLibrary::FindLookAtRotation(HandLocation, ImpactPoint);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	UWorld* World = GetWorld();
	if (World)
	{
		switch (AttackType)
		{
		case EAttackType::SimpleAttack:
			World->SpawnActor<AActor>(BasicAttackProjectileClass, HandLocation, SpawnRotation, SpawnParams);
			break;
		case EAttackType::BlackHole:
			World->SpawnActor<AActor>(BlackHoleProjectileClass, HandLocation, SpawnRotation, SpawnParams);
			break;
		case EAttackType::Teleport:
			World->SpawnActor<AActor>(TeleportProjectileClass, HandLocation, SpawnRotation, SpawnParams);
			break;
		case EAttackType::MAX:
			break;

		}
	}
	bCanFire = true;
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ASCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.f;
	ControlRot.Roll = 0.f;
	AddMovementInput(ControlRot.Vector(), Value);
}

void ASCharacter::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.f;
	ControlRot.Roll = 0.f;

	AddMovementInput(FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y), Value);
}

void ASCharacter::PrimaryAttack()
{
	if (bCanFire)
	{
		PlayAnimMontage(AttackAnim);
		bCanFire = false;
		GetWorldTimerManager().SetTimer(PrimaryAttackTimerHandle, this, &ThisClass::PrimaryAttackTimeElapsed, 0.2f);
	}
}

void ASCharacter::PrimaryInteract()
{
	InteractionComp->PrimaryInteract();
}

void ASCharacter::OnHealthChanged(AActor* InstigatorActor, USAttributesComponent* OwningComp, float NewHealth, float Delta)
{
	if (NewHealth <= 0.0f && Delta < 0.0f)
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		DisableInput(PC);
	}
}

void ASCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributesComp->OnHealthChanged.AddDynamic(this, &ThisClass::OnHealthChanged);
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TraceUnderCrosshair();
}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ASCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction(TEXT("PrimaryAttack"), IE_Pressed, this, &ThisClass::PrimaryAttack);
	PlayerInputComponent->BindAction(TEXT("PrimaryInteract"), IE_Pressed, this, &ThisClass::PrimaryInteract);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("SimpleAttackType"), IE_Pressed, this, &ThisClass::ChangeAttackTypeToSimple);
	PlayerInputComponent->BindAction(TEXT("BlackHoleAttackType"), IE_Pressed, this, &ThisClass::ChangeAttackTypeToBlackHole);
	PlayerInputComponent->BindAction(TEXT("TeleportAttackType"), IE_Pressed, this, &ThisClass::ChangeAttackTypeToTeleport);
}

void ASCharacter::TraceUnderCrosshair()
{
	FVector2D ViewportSize;
	GEngine->GameViewport->GetViewportSize(ViewportSize);

	FVector CrosshairWorldLocation;
	FVector CrosshairWorldDirection;

	bool bScreenToWorld = UGameplayStatics::DeprojectScreenToWorld(UGameplayStatics::GetPlayerController(this, 0), ViewportSize * 0.5f, CrosshairWorldLocation, CrosshairWorldDirection);

	if (bScreenToWorld)
	{
		const float DistanceToCharacter = (CrosshairWorldLocation - GetActorLocation()).Size();
		FVector StartPoint = CrosshairWorldLocation + (DistanceToCharacter + 100.f) * CrosshairWorldDirection;
		FVector EndPoint = CrosshairWorldLocation + CrosshairWorldDirection * TRACE_LENGTH;

		FHitResult HitResult;
		GetWorld()->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, ECollisionChannel::ECC_Visibility);
		ImpactPoint = !HitResult.bBlockingHit ? EndPoint : HitResult.ImpactPoint;
	}
}

void ASCharacter::ChangeAttackTypeToTeleport()
{
	UE_LOG(PLAYER, Display, TEXT("Changed attack type to TELEPORT"));
	AttackType = EAttackType::Teleport;
}

void ASCharacter::ChangeAttackTypeToSimple()
{
	UE_LOG(PLAYER, Display, TEXT("Changed attack type to SIMPLE"));
	AttackType = EAttackType::SimpleAttack;
}

void ASCharacter::ChangeAttackTypeToBlackHole()
{
	UE_LOG(PLAYER, Display, TEXT("Changed attack type to BLACKHOLE"));
	AttackType = EAttackType::BlackHole;
}
