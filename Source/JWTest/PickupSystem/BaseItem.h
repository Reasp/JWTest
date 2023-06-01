// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseItem.generated.h"

class ABaseWeapon;
class ABaseItem;
class USphereComponent;
class USkeletalMeshComponent;

USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABaseWeapon> ItemClass;
};

UCLASS(Abstract)
class JWTEST_API ABaseItem : public AActor
{
	GENERATED_BODY()

	/** pickup on touch */
	virtual void NotifyActorBeginOverlap(class AActor* Other) override;

public:
	// Sets default values for this actor's properties
	ABaseItem();

	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                    const FHitResult& SweepResult);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* PickupSphere;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* SkeletalMesh;
private:
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	FItemData ItemData;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	float PickupRadius = 100.f;
};
