// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"

#include "JWPlayerController.h"
#include "JWTestGameModeBase.h"
#include "Camera/CameraComponent.h"
#include "PickupSystem/InventoryComponent.h"
#include "Weapon/BaseWeapon.h"
// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(RootComponent);
	CameraComponent->bUsePawnControlRotation = true;

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
}

void APlayerCharacter::SpawnWeapon(const TSubclassOf<ABaseWeapon>& Class)
{
	if (Class)
	{
		if (CurrentWeapon)
		{
			CurrentWeapon->Destroy();
		}

		CurrentWeapon = GetWorld()->SpawnActor<ABaseWeapon>(Class);
		if (CurrentWeapon)
		{
			CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale,
			                                 TEXT("WeaponSocket"));
			CurrentWeapon->SetOwner(this);
		}
	}
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	if (WeaponClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Try to spawn weapon"));
		SpawnWeapon(WeaponClass);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::Destroyed()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->Destroy();
	}

	Super::Destroyed();
}

void APlayerCharacter::MoveForward(float InValue)
{
	if (InValue != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), InValue);
	}
}

void APlayerCharacter::MoveRight(float InValue)
{
	if (InValue != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), InValue);
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::OnFire);


	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void APlayerCharacter::AddItemToInventory(ABaseItem* InBaseItem)
{
}

void APlayerCharacter::SetCurrentWeapon(ABaseWeapon* InWeapon)
{
}

void APlayerCharacter::OnFire()
{
	UE_LOG(LogTemp, Warning, TEXT("APlayerCharacter::OnFire"));
	if (CurrentWeapon)
	{
		CurrentWeapon->Fire();
	}
}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                                   AActor* DamageCauser)
{
	float AppliedDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	AppliedDamage = FMath::Min(Health, AppliedDamage);

	Health -= AppliedDamage;

	if (Health <= 0.0f)
	{
		Die();
	}
	return AppliedDamage;
}

void APlayerCharacter::Die()
{
	UE_LOG(LogTemp, Warning, TEXT("APlayerCharacter::Die"));
	AJWPlayerController* PlayerController = Cast<AJWPlayerController>(GetController());

	AJWTestGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AJWTestGameModeBase>();
	if (GameMode && PlayerController)
	{
		DetachFromControllerPendingDestroy();
		SetLifeSpan(10.0f);
		GameMode->RestartPlayer(PlayerController);
	}
}
