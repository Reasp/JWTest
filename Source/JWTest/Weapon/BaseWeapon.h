// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

class UFireAction;
class USkeletalMeshComponent;
class USceneComponent;

UCLASS(BlueprintType, Abstract)
class JWTEST_API ABaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UFireAction> FireActionClass;

	UPROPERTY()
	UFireAction* FireActionObject;

	UPROPERTY()
	APawn* OwnerPawn;

public:
	void Fire();
};
