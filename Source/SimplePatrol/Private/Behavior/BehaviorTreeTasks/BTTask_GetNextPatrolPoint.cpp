// Fill out your copyright notice in the Description page of Project Settings.

#include "Behavior/BehaviorTreeTasks/BTTask_GetNextPatrolPoint.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Patrol/PatrolNpcAIController.h"

UBTTask_GetNextPatrolPoint::UBTTask_GetNextPatrolPoint()
{
	NodeName = TEXT("Get Next Patrol Point");
	GoalLocationKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_GetNextPatrolPoint, GoalLocationKey));
}

void UBTTask_GetNextPatrolPoint::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
	
	if (const UBlackboardData* BlackboardAsset = GetBlackboardAsset())
	{
		GoalLocationKey.ResolveSelectedKey(*BlackboardAsset);
	}
}

EBTNodeResult::Type UBTTask_GetNextPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APatrolNpcAIController* Controller = Cast<APatrolNpcAIController>(OwnerComp.GetAIOwner());
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	FVector Goal = FVector::ZeroVector;
	
	if (!Controller || !Blackboard || !Controller->TryGetPatrolLocation(Goal))
	{
		return EBTNodeResult::Failed;
	}
	
	Blackboard->SetValueAsVector(GoalLocationKey.SelectedKeyName, Goal);
	return EBTNodeResult::Succeeded;
}