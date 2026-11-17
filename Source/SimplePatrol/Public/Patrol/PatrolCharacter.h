// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetWeaponMesh(UStaticMesh* InWeaponMesh, FName SocketName) const;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Patrol")
	FName ID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Patrol")
	TObjectPtr<UStaticMeshComponent> WeaponMesh;
};
