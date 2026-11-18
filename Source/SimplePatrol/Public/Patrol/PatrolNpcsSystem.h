// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PatrolCharacter.h"
#include "Data/PatrolCharacterData.h"
#include "Subsystems/WorldSubsystem.h"
#include "PatrolNpcsSystem.generated.h"

struct FPatrolCharacterData;

/**
 * 
 */
UCLASS()
class SIMPLEPATROL_API UPatrolNpcsSystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Deinitialize() override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	
	void RegisterPatrolNpcActor(APatrolCharacter* PatrolNpcActor);
	void UnregisterPatrolNpcActor(APatrolCharacter* PatrolNpcActor);
	
private:
	bool GetPatrolCharacterDataFromConfig(const FName& PatrolId, FPatrolCharacterData& PatrolCharacterDataOut) const;
	bool GetPatrolDataForID(const FName& PatrolID,
		UPatrolCharacterDataDefinition*& PatrolCharacterDataDefinitionOut,
		APatrolCharacterRoute*& PatrolCharacterRouteOut) const;
	
public:
	UPROPERTY(BlueprintReadOnly, Category="Patrol")
	TObjectPtr<UDataTable> PatrolCharacterData;
	
private:
	UPROPERTY()
	TArray<TWeakObjectPtr<APatrolCharacter>> PatrolNpcs;
};
