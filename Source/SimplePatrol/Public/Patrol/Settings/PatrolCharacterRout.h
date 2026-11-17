// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "PatrolCharacterRout.generated.h"

UCLASS(BlueprintType, Blueprintable)
class SIMPLEPATROL_API APatrolCharacterRout : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	APatrolCharacterRout();
	
	UFUNCTION(Blueprintable, BlueprintType)
	FVector3d GetStartPosition() const
	{
		return GetTransform().GetLocation();
	}
	
	UFUNCTION(Blueprintable, BlueprintType)
	void GetPatrolRoutPoints(TArray<FVector3d>& PatrolRoutPoints) const;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Rout")
	TObjectPtr<USplineComponent> SplineComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Rout")
	int RoutDistanceMultiplier = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="RoutParameters")
	bool bLoop;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="RoutParameters")
	bool bReverseOnEnd;

};
