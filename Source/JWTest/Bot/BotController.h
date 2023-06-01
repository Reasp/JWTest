// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BotController.generated.h"

class UBehaviorTreeComponent;
/**
 * 
 */
UCLASS()
class JWTEST_API ABotController : public AAIController
{
	GENERATED_BODY()
private:
	UPROPERTY(transient)
	UBlackboardComponent* BlackboardComp;

	/* Cached BT component */
	UPROPERTY(transient)
	UBehaviorTreeComponent* BehaviorComp;
};
