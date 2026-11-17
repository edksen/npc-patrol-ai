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
		SetUpPatrolNpc(PatrolNpcActor);
	}
}

void UPatrolNpcsSystem::SetUpPatrolNpc(APatrolCharacter* PatrolNpcActor) const
{
	FPatrolCharacterData PatrolCharacterDataFromConfig;
	if(!GetPatrolCharacterDataFromConfig(PatrolNpcActor->ID, PatrolCharacterDataFromConfig))
		return;
	
	FSoftObjectPath PatrolDefinitionPath = PatrolCharacterDataFromConfig.PatrolDefinitionData.ToSoftObjectPath();
	if (!PatrolDefinitionPath.IsNull())
	{
		const UPatrolCharacterDataDefinition* PatrolCharacterDataDefinition = PatrolCharacterDataFromConfig.PatrolDefinitionData.LoadSynchronous();
		check(PatrolCharacterDataDefinition != nullptr);
		
		if (USkeletalMeshComponent* PatrolNpcMesh = PatrolNpcActor->GetMesh())
		{
			const auto PatrolMesh = PatrolCharacterDataDefinition->PatrolMeshComponent.LoadSynchronous();
			const auto PatrolWeaponMesh = PatrolCharacterDataDefinition->PatrolArmStaticMesh.LoadSynchronous();
			
			const auto PatrolAnimation = PatrolCharacterDataDefinition->PatrolCharacterAnim.LoadSynchronous();
			check(PatrolAnimation != nullptr);
			const auto PatrolAnimBlueprintClass = PatrolAnimation ->GetAnimBlueprintGeneratedClass();
			
			check(PatrolMesh != nullptr);
			check(PatrolWeaponMesh != nullptr);
			check(PatrolAnimBlueprintClass != nullptr);
			
			PatrolNpcMesh->SetSkeletalMeshAsset(PatrolMesh);
			PatrolNpcMesh->SetAnimInstanceClass(PatrolAnimBlueprintClass);
			PatrolNpcActor->SetWeaponMesh(PatrolWeaponMesh, PatrolCharacterDataDefinition->PatrolWeaponSocket);
		}
		
		//TODO Add rout setup here
	}
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
