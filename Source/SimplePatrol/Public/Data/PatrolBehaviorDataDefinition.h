// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PatrolBehaviorDataDefinition.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEPATROL_API UPatrolBehaviorDataDefinition : public UDataAsset
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, Category="PatrolBehavior", meta=(AllowedClasses="/Script/AIModule.BehaviorTree,/Script/StateTreeModule.StateTree"))
	TSoftObjectPtr<UObject> PatrolBehavior;
};
