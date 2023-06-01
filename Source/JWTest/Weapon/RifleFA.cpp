// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/RifleFA.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

void URifleFA::StartFire(FRotator InRotation, FVector InLocation)
{
	Super::StartFire(InRotation, InLocation);

	UWorld* const World = GetWorld();
	checkf(World, TEXT("UShotgunFA::StartFire World is nullptr"));
	// Trace from camera to check what's under crosshair
	FHitResult Hit;
	const FVector EndTrace = InLocation + InRotation.Vector() * WeaponRange;
	World->LineTraceSingleByChannel(Hit, InLocation, EndTrace,
	                                ECollisionChannel::ECC_Camera);

	FVector TrailEnd = EndTrace;
	// If we hit something
	if (Hit.bBlockingHit)
	{
		// Get the actor that was hit
		AActor* HitActor = Hit.GetActor();
		// If we hit an actor
		if (HitActor)
		{
			HitActor->TakeDamage(WeaponDamage, FDamageEvent(), nullptr, nullptr);
		}
		TrailEnd = Hit.ImpactPoint;
	}
	SpawnTrailEffect(InLocation, TrailEnd);
}

void URifleFA::SpawnTrailEffect(FVector StartLocation, FVector EndLocation)
{
	if (TrailEffect)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnTrailEffect"));
		UParticleSystemComponent* Trail = UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(), TrailEffect, StartLocation);
		if (Trail)
		{
			Trail->SetVectorParameter(TrailTargetParam, EndLocation);
		}
	}
}

void URifleFA::SpawnImpactEffect(FVector Location, FRotator Rotation)
{
}
