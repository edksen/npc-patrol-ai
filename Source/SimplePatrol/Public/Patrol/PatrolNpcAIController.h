// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Components/StateTreeAIComponent.h"
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
	APatrolNpcAIController();
	void SetPatrolRouteData(APatrolCharacterRoute* PatrolRouteData);
	
	void SetPatrolBehavior(UObject* PatrolBehavior);
	
	UFUNCTION(BlueprintCallable, Category="Patrol")
	bool TryGetPatrolLocation(FVector& PatrolLocationOut);
	
private:
	void SetAIStateTree(UStateTree* AIStateTree) const;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<APatrolCharacterRoute> PatrolRoute;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStateTreeAIComponent> StateTreeComponent;

	int32 CurrentPointIndex = 0;
	int32 Direction = 1;
};
