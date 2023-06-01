// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/ShotgunFA.h"

#include "BaseProjectile.h"

void UShotgunFA::StartFire(FRotator InAimRotation, FVector InLocation)
{
	Super::StartFire(InAimRotation, InLocation);
	checkf(ProjectileClass != nullptr, TEXT("ProjectileClass not selected"));

	UWorld* const World = GetWorld();
	checkf(World, TEXT("UShotgunFA::StartFire World is nullptr"));
	const FQuat ShootRotation = FQuat::FindBetweenNormals(FVector::ForwardVector, InAimRotation.Vector());
	UE_LOG(LogTemp, Warning, TEXT("UShotgunFA::StartFire try to spawn projectiles"));
	// Fire multiple pellets
	for (int32 i = 0; i < PelletsCount; i++)
	{
		// Calculate a random direction within the spread angle
		const FQuat ConeOffset(FVector::UpVector, FMath::FRandRange(-MaxSpreadAngle, MaxSpreadAngle));
		const FVector PelletDirection = ShootRotation.RotateVector(ConeOffset.RotateVector(FVector::ForwardVector));

		// Spawn a projectile or perform hit detection with the PelletDirection and ShootLocation
		//Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		// spawn the projectile at the muzzle
		World->SpawnActor<ABaseProjectile>(ProjectileClass, InLocation, PelletDirection.Rotation(), ActorSpawnParams);
	}
}

UShotgunFA::UShotgunFA()
{
	//Calculate the spread angle based on the number of pellets and spread radius
	MaxSpreadAngle = FMath::DegreesToRadians(FMath::Atan(SpreadRadius / SpreadDistance));
}
