// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/FireAction.h"
#include "ShotgunFA.generated.h"

class ABaseProjectile;
/**
 * 
 */
UCLASS()
class JWTEST_API UShotgunFA : public UFireAction
{
	GENERATED_BODY()
public:
	UShotgunFA();

	virtual void StartFire(FRotator InAimRotation, FVector InLocation) override;
private:
	UPROPERTY(EditDefaultsOnly, Category= "Settings")
	int32 PelletsCount = 8;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	float SpreadRadius = 100.f;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	float SpreadDistance = 100.f;

	float MaxSpreadAngle;
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TSubclassOf<ABaseProjectile> ProjectileClass;
};
