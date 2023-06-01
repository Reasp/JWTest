// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/FireAction.h"
#include "RifleFA.generated.h"

/**
 * 
 */
UCLASS()
class JWTEST_API URifleFA : public UFireAction
{
	GENERATED_BODY()
public:
	virtual void StartFire(FRotator InRotation, FVector InLocation) override;
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	UParticleSystem* TrailEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	float WeaponRange = 10000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	float WeaponDamage = 10.f;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	FName TrailTargetParam;

	void SpawnTrailEffect(FVector StartLocation, FVector EndLocation);

	void SpawnImpactEffect(FVector Location, FRotator Rotation);
};
