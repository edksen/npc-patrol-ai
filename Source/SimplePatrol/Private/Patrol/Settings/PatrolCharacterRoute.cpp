// Fill out your copyright notice in the Description page of Project Settings.


#include "Patrol/Settings/PatrolCharacterRoute.h"

APatrolCharacterRoute::APatrolCharacterRoute()
{
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("PatrolRout"));
	check(SplineComponent != nullptr);
	RootComponent = SplineComponent;
}

void APatrolCharacterRoute::GetPatrolRoutPoints(TArray<FVector3d>& PatrolRoutPoints) const
{
	int32 SplinePointsNumber = SplineComponent->GetNumberOfSplinePoints();
	for (int32 SplinePoint = 0; SplinePoint < SplinePointsNumber; SplinePoint++)
	{
		PatrolRoutPoints.Add(SplineComponent->GetLocationAtSplinePoint(SplinePoint, ESplineCoordinateSpace::World) * RoutDistanceMultiplier);
	}
}
