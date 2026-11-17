// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PatrolCharacterDataDefinition.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class SIMPLEPATROL_API UPatrolCharacterDataDefinition : public UDataAsset
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, Category="PatrolCharacterData")
	FName PatrolID;
	
	UPROPERTY(EditAnywhere, Category="PatrolMesh")
	TSoftObjectPtr<USkeletalMesh> PatrolMeshComponent;
	
	UPROPERTY(EditAnywhere, Category="PatrolMesh")
	TSoftObjectPtr<UStaticMesh> PatrolArmStaticMesh;

	UPROPERTY(EditAnywhere, Category="PatrolMesh")
	FName PatrolWeaponSocket = TEXT("ik_hand_gun");
	
	UPROPERTY(EditAnywhere, Category="PatrolAnimation")
	TSoftObjectPtr<UAnimBlueprint> PatrolCharacterAnim;
};
