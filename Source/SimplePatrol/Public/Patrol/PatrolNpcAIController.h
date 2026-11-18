// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Settings/PatrolCharacterRoute.h"
#include "PatrolNpcAIController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEPATROL_API APatrolNpcAIController : public AAIController
{
	GENERATED_BODY()
public:
	void SetPatrolRoute(APatrolCharacterRoute* PatrolRouteData)
	{
		check(PatrolRouteData != nullptr);
		PatrolRoute = PatrolRouteData;
	}
	
private:
	UPROPERTY()
	TObjectPtr<APatrolCharacterRoute> PatrolRoute;
};
