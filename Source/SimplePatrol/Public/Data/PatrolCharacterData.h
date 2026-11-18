// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PatrolCharacterDataDefinition.h"
#include "Patrol/Settings/PatrolCharacterRoute.h"
#include "PatrolCharacterData.generated.h"

class UPatrolCharacterDataDefinition;
class APatrolCharacterRoute;

USTRUCT(BlueprintType, Blueprintable)
struct FPatrolCharacterData: public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category="PatrolData")
	FName ID;
	
	UPROPERTY(EditAnywhere, Category="PatrolData")
	TSoftObjectPtr<UPatrolCharacterDataDefinition> PatrolDefinitionData;
	
	UPROPERTY(EditAnywhere, Category="RouteData")
	TSoftObjectPtr<APatrolCharacterRoute> PatrolCharacterRoute;
};

