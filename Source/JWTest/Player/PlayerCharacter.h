// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PickupSystem/BaseItem.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class ABaseWeapon;
class UInventoryComponent;
struct FInputActionValue;
UCLASS()
class JWTEST_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	void SpawnWeapon(const TSubclassOf<ABaseWeapon>& Class);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** socket or bone name for attaching weapon mesh */
	UPROPERTY(EditDefaultsOnly, Category = Inventory)
	FName WeaponAttachPoint;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Destroyed() override;

	UFUNCTION()
	void MoveForward(float InValue);

	UFUNCTION()
	void MoveRight(float InValue);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AddItemToInventory(ABaseItem* InBaseItem);

	void SetCurrentWeapon(ABaseWeapon* InWeapon);

	UFUNCTION()
	void OnFire();

	UFUNCTION(BlueprintPure, Category= "Player")
	bool IsDead() const { return Health <= 0.0f; };

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	                         AActor* DamageCauser) override;
	void Die();
private:
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	float MaxHealth = 100.0f;

	float Health;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TSubclassOf<ABaseWeapon> WeaponClass;

	ABaseWeapon* CurrentWeapon;

	UPROPERTY(VisibleAnywhere)
	UInventoryComponent* InventoryComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;
};
