#include "Behavior/StateTreeTasks/StateTreeTask_GetNextPatrolPoint.h"

#include "StateTreeExecutionContext.h"
#include "Patrol/PatrolNpcAIController.h"

EStateTreeRunStatus FStateTreeTask_GetNextPatrolPoint::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	FInstanceDataType& Data = Context.GetInstanceData(*this);
	APatrolNpcAIController* Controller = Cast<APatrolNpcAIController>(Data.AIController);
	if (!Controller || !Controller->TryGetPatrolLocation(Data.GoalLocation))
	{
		return EStateTreeRunStatus::Failed;
	}
	
	return EStateTreeRunStatus::Succeeded;
}
