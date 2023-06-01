// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FireAction.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, Abstract)
class JWTEST_API UFireAction : public UObject
{
	GENERATED_BODY()
public:
	virtual void StartFire(FRotator InRotation, FVector InLocation);
};
