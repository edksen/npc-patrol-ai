// Fill out your copyright notice in the Description page of Project Settings.


#include "Patrol/PatrolNpcsSystem.h"
#include "Patrol/Settings/PatrolControllerSettings.h"

void UPatrolNpcsSystem::Deinitialize()
{
	Super::Deinitialize();
	
	PatrolNpcs.Reset();
}

void UPatrolNpcsSystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	
	const UPatrolControllerSettings* PatrolSettings = GetDefault<UPatrolControllerSettings>();
	check(PatrolSettings != nullptr);
	
	PatrolCharacterData = PatrolSettings->PatrolConfigTable.LoadSynchronous();
	check(PatrolCharacterData != nullptr);
}

void UPatrolNpcsSystem::RegisterPatrolNpcActor(APatrolCharacter* PatrolNpcActor)
{
	if (PatrolNpcActor)
	{
		PatrolNpcs.Add(PatrolNpcActor);
		UPatrolCharacterDataDefinition* PatrolCharacterDataDefinition = nullptr;
		APatrolCharacterRoute* PatrolCharacterRoute = nullptr;
		
		if(GetPatrolDataForID(PatrolNpcActor->ID, PatrolCharacterDataDefinition, PatrolCharacterRoute))
			PatrolNpcActor->ApplyPatrolDataDefinition(PatrolCharacterDataDefinition, PatrolCharacterRoute);
	}
}

void UPatrolNpcsSystem::UnregisterPatrolNpcActor(APatrolCharacter* PatrolNpcActor)
{
	if (PatrolNpcActor)
	{
		PatrolNpcs.Remove(PatrolNpcActor);
	}
}

bool UPatrolNpcsSystem::GetPatrolDataForID(const FName& PatrolID, UPatrolCharacterDataDefinition*& PatrolCharacterDataDefinitionOut, APatrolCharacterRoute*& PatrolCharacterRouteOut) const
{
	FPatrolCharacterData PatrolCharacterDataFromConfig;
	if(GetPatrolCharacterDataFromConfig(PatrolID, PatrolCharacterDataFromConfig))
	{
		FSoftObjectPath PatrolDefinitionPath = PatrolCharacterDataFromConfig.PatrolDefinitionData.ToSoftObjectPath();
		if (!PatrolDefinitionPath.IsNull())
		{
			PatrolCharacterDataDefinitionOut = PatrolCharacterDataFromConfig.PatrolDefinitionData.LoadSynchronous();
			PatrolCharacterRouteOut = PatrolCharacterDataFromConfig.PatrolCharacterRoute.LoadSynchronous();
			
			return ensureMsgf(PatrolCharacterDataDefinitionOut && PatrolCharacterRouteOut,
				TEXT("Patrol ID '%s': Something went wrong loading Definition or Route"), *PatrolID.ToString());
		}
	}
	
	return ensureMsgf(false, TEXT("Patrol ID '%s': Can't find data for ID"), *PatrolID.ToString());
}

bool UPatrolNpcsSystem::GetPatrolCharacterDataFromConfig(const FName& PatrolId, FPatrolCharacterData& PatrolCharacterDataOut) const
{
	if (PatrolCharacterData && !PatrolId.IsNone())
	{
		if (const FPatrolCharacterData* Row = PatrolCharacterData->FindRow<FPatrolCharacterData>(PatrolId, PatrolId.ToString()))
		{
			PatrolCharacterDataOut = *Row;
			return true;
		}
	}
	
	return false;
}
