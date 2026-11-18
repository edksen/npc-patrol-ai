// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "PatrolCharacterRoute.generated.h"

UCLASS(BlueprintType, Blueprintable)
class SIMPLEPATROL_API APatrolCharacterRoute : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	APatrolCharacterRoute();
	
	UFUNCTION(Blueprintable, BlueprintType)
	FVector3d GetStartPosition() const
	{
		return GetTransform().GetLocation();
	}
	
	UFUNCTION(Blueprintable, BlueprintType)
	void GetPatrolRoutPoints(TArray<FVector3d>& PatrolRoutPoints) const;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Route")
	TObjectPtr<USplineComponent> SplineComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Route")
	int RoutDistanceMultiplier = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="RouteParameters")
	bool bLoop;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="RouteParameters")
	bool bReverseOnEnd;

};
