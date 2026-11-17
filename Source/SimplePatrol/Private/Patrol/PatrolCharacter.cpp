// Fill out your copyright notice in the Description page of Project Settings.


#include "Patrol/PatrolCharacter.h"

// Sets default values
APatrolCharacter::APatrolCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(GetMesh());
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void APatrolCharacter::SetWeaponMesh(UStaticMesh* InWeaponMesh, FName SocketName) const
{
	if (!WeaponMesh || !GetMesh())
	{
		return;
	}

	WeaponMesh->SetStaticMesh(InWeaponMesh);
	WeaponMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
}

// Called when the game starts or when spawned
void APatrolCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APatrolCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

