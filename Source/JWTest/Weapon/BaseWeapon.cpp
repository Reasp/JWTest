// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/BaseWeapon.h"

#include "FireAction.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"


// Sets default values
ABaseWeapon::ABaseWeapon()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(Root);

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	if (FireActionClass != nullptr)
	{
		FireActionObject = NewObject<UFireAction>(this, FireActionClass);
		checkf(FireActionObject, TEXT("FireActionObject is nullptr"));
	}
}

void ABaseWeapon::Fire()
{
	OwnerPawn = Cast<APawn>(GetOwner());
	checkf(OwnerPawn, TEXT("OwnerPawn is nullptr"));
	checkf(SkeletalMesh, TEXT("SkeletalMesh is nullptr"));
	const FRotator SpawnRotation = OwnerPawn->GetControlRotation();
	const FVector SpawnLocation = SkeletalMesh->GetSocketLocation(TEXT("MuzzleFlashSocket"));

	if (FireActionObject)
	{
		UE_LOG(LogTemp, Warning, TEXT("FireActionObject is not nullptr"));
		FireActionObject->StartFire(SpawnRotation, SpawnLocation);
	}
}
