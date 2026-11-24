// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_GetNextPatrolPoint.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEPATROL_API UBTTask_GetNextPatrolPoint : public UBTTaskNode
{
	GENERATED_BODY()
public: 
	UBTTask_GetNextPatrolPoint();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
protected:
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	
	UPROPERTY(EditAnywhere, Category="Blackboard")
	FBlackboardKeySelector GoalLocationKey;
};
