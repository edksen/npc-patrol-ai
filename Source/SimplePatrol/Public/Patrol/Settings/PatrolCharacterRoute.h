// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "PatrolCharacterRoute.generated.h"

UENUM(BlueprintType)
enum class EPatrolRouteTraversal : uint8
{
	Once,
	Loop,
	PingPong
};

UCLASS(BlueprintType, Blueprintable)
class SIMPLEPATROL_API APatrolCharacterRoute : public AActor
{
	GENERATED_BODY()
	
public:
	APatrolCharacterRoute();

	UFUNCTION(BlueprintCallable, Category="Route")
	FVector GetStartPosition() const;

	UFUNCTION(BlueprintCallable, Category="Route")
	int32 GetPointCount() const;

	UFUNCTION(BlueprintCallable, Category="Route")
	FVector GetPointAt(int32 PointIndex) const;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Route")
	TObjectPtr<USplineComponent> SplineComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Route")
	EPatrolRouteTraversal Traversal = EPatrolRouteTraversal::Loop;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Route")
	float MaximumWalkSpeed = 200.f;
};
