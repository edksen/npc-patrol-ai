#pragma once
#include "AIController.h"
#include "Tasks/StateTreeAITask.h"
#include "StateTreeTask_GetNextPatrolPoint.generated.h"

USTRUCT()
struct FStateTreeGetNextPatrolPointInstanceData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Context")
	TObjectPtr<AAIController> AIController = nullptr;
	
	UPROPERTY(EditAnywhere, Category = "Output")
	FVector GoalLocation = FVector::ZeroVector;
};


USTRUCT(meta = (DisplayName = "Get Next Patrol Point", Category = "AI"))
struct FStateTreeTask_GetNextPatrolPoint : public FStateTreeAITaskBase
{
	GENERATED_BODY()
	
	using FInstanceDataType = FStateTreeGetNextPatrolPointInstanceData;
	
	FStateTreeTask_GetNextPatrolPoint()
	{
		bShouldCallTick = false;
	}
	
	virtual const UStruct* GetInstanceDataType() const override
	{
		return FInstanceDataType::StaticStruct();
	}
	
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
};
