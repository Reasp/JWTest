// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupSystem/BaseItem.h"

#include "Components/SphereComponent.h"
#include "Player/PlayerCharacter.h"
#include "Weapon/BaseWeapon.h"


// Sets default values
ABaseItem::ABaseItem()
{
	PickupSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PickupSphere"));
	SetRootComponent(PickupSphere);
	PickupSphere->SetSphereRadius(PickupRadius);

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(PickupSphere);
}

void ABaseItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                               const FHitResult& SweepResult)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		PlayerCharacter->AddItemToInventory(this);
	}
}

// Called when the game starts or when spawned
void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseItem::NotifyActorBeginOverlap(AActor* Other)
{
	Super::NotifyActorBeginOverlap(Other);

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Other);
	if (PlayerCharacter && ItemData.ItemClass != nullptr)
	{
		PlayerCharacter->SpawnWeapon(ItemData.ItemClass);
	}
}
