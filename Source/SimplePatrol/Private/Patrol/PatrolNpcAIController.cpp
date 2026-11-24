// Fill out your copyright notice in the Description page of Project Settings.


#include "Patrol/PatrolNpcAIController.h"

#include "StateTree.h"
#include "BehaviorTree/BehaviorTree.h"

APatrolNpcAIController::APatrolNpcAIController()
{
	StateTreeComponent = CreateDefaultSubobject<UStateTreeAIComponent>(TEXT("StateTreeAIComponent"));
	StateTreeComponent->SetStartLogicAutomatically(false);
}

void APatrolNpcAIController::SetPatrolRouteData(APatrolCharacterRoute* PatrolRouteData)
{
	check(PatrolRouteData != nullptr);
	PatrolRoute = PatrolRouteData;
	CurrentPointIndex = 0;
	Direction = 1;
}

void APatrolNpcAIController::SetPatrolBehavior(UObject* PatrolBehavior)
{
	if (UBehaviorTree* BehaviorTree = Cast<UBehaviorTree>(PatrolBehavior))
	{
		RunBehaviorTree(BehaviorTree);
	}
	else if (UStateTree* StateTree = Cast<UStateTree>(PatrolBehavior))
	{
		SetAIStateTree(StateTree);
	}
}

void APatrolNpcAIController::SetAIStateTree(UStateTree* AIStateTree) const
{
	check(AIStateTree != nullptr);
	StateTreeComponent->SetStateTree(AIStateTree);
	StateTreeComponent->StartLogic();
}

bool APatrolNpcAIController::TryGetPatrolLocation(FVector& PatrolLocationOut)
{
	if (!PatrolRoute || PatrolRoute->GetPointCount() == 0)
	{
		PatrolLocationOut = GetPawn() ? GetPawn()->GetActorLocation() : FVector::ZeroVector;
		return false;
	}

	const int32 PointCount = PatrolRoute->GetPointCount();
	if (PointCount == 1)
	{
		CurrentPointIndex = 0;
		PatrolLocationOut = PatrolRoute->GetPointAt(0);
		return false;
	}

	int32 NextIndex = CurrentPointIndex + Direction;
	switch (PatrolRoute->Traversal)
	{
	case EPatrolRouteTraversal::Loop:
		if (NextIndex >= PointCount)
		{
			NextIndex = 0;
		}
		else if (NextIndex < 0)
		{
			NextIndex = PointCount - 1;
		}
		break;
	case EPatrolRouteTraversal::PingPong:
		if (NextIndex >= PointCount)
		{
			Direction = -1;
			NextIndex = PointCount - 2;
		}
		else if (NextIndex < 0)
		{
			Direction = 1;
			NextIndex = 1;
		}
		break;
	case EPatrolRouteTraversal::Once:
	default:
		NextIndex = FMath::Clamp(NextIndex, 0, PointCount - 1);
		break;
	}

	PatrolLocationOut = PatrolRoute->GetPointAt(NextIndex);
	if (CurrentPointIndex == NextIndex)
	{
		return false;
	}
	
	CurrentPointIndex = NextIndex;
	return true;
}
