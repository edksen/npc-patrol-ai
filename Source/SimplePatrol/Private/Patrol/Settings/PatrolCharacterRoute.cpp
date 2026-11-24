// Fill out your copyright notice in the Description page of Project Settings.


#include "Patrol/Settings/PatrolCharacterRoute.h"

APatrolCharacterRoute::APatrolCharacterRoute()
{
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("PatrolRout"));
	check(SplineComponent != nullptr);
	RootComponent = SplineComponent;
}

FVector APatrolCharacterRoute::GetStartPosition() const
{
	if (GetPointCount() == 0)
	{
		return GetActorLocation();
	}

	return GetPointAt(0);
}

int32 APatrolCharacterRoute::GetPointCount() const
{
	return SplineComponent ? SplineComponent->GetNumberOfSplinePoints() : 0;
}

FVector APatrolCharacterRoute::GetPointAt(int32 PointIndex) const
{
	if (!SplineComponent || PointIndex < 0 || PointIndex >= SplineComponent->GetNumberOfSplinePoints())
	{
		return GetActorLocation();
	}

	return SplineComponent->GetLocationAtSplinePoint(PointIndex, ESplineCoordinateSpace::World);
}
