// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Data/PatrolBehaviorDataDefinition.h"
#include "Data/PatrolCharacterDataDefinition.h"
#include "GameFramework/Character.h"
#include "Settings/PatrolCharacterRoute.h"
#include "PatrolCharacter.generated.h"

UCLASS(BlueprintType, Blueprintable)
class SIMPLEPATROL_API APatrolCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APatrolCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void ApplyPatrolDataDefinition(const UPatrolCharacterDataDefinition* PatrolCharacterDataDefinition, APatrolCharacterRoute* PatrolCharacterRoute, const UPatrolBehaviorDataDefinition* PatrolBehaviorDataDefinition);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Patrol")
	FName ID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Patrol")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;
	
private:
	void SetWeaponMesh(USkeletalMesh* InWeaponMesh, FName SocketName) const;
};
