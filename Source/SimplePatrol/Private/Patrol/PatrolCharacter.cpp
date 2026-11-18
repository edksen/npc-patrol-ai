// Fill out your copyright notice in the Description page of Project Settings.


#include "Patrol/PatrolCharacter.h"
#include "Patrol/PatrolNpcAIController.h"
#include "Patrol/PatrolNpcsSystem.h"

// Sets default values
APatrolCharacter::APatrolCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(GetMesh());
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	AIControllerClass = APatrolNpcAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void APatrolCharacter::SetWeaponMesh(USkeletalMesh* InWeaponMesh, FName SocketName) const
{
	if (!WeaponMesh || !GetMesh())
	{
		return;
	}

	WeaponMesh->SetSkeletalMesh(InWeaponMesh);
	WeaponMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
}

void APatrolCharacter::ApplyPatrolDataDefinition(const UPatrolCharacterDataDefinition* PatrolCharacterDataDefinition, APatrolCharacterRoute* PatrolCharacterRoute)
{
	if (USkeletalMeshComponent* PatrolNpcMesh = GetMesh())
	{
		const auto PatrolMesh = PatrolCharacterDataDefinition->PatrolMeshComponent.LoadSynchronous();
		const auto PatrolWeaponMesh = PatrolCharacterDataDefinition->PatrolArmSkeletalMesh.LoadSynchronous();
			
		const auto PatrolAnimation = PatrolCharacterDataDefinition->PatrolCharacterAnim.LoadSynchronous();
		check(PatrolAnimation != nullptr);
		const auto PatrolAnimBlueprintClass = PatrolAnimation ->GetAnimBlueprintGeneratedClass();
			
		check(PatrolMesh != nullptr);
		check(PatrolWeaponMesh != nullptr);
		check(PatrolAnimBlueprintClass != nullptr);
			
		PatrolNpcMesh->SetSkeletalMeshAsset(PatrolMesh);
		PatrolNpcMesh->SetAnimInstanceClass(PatrolAnimBlueprintClass);
		SetWeaponMesh(PatrolWeaponMesh, PatrolCharacterDataDefinition->PatrolWeaponSocket);
	}
	
	if(APatrolNpcAIController* AIController = Cast<APatrolNpcAIController>(GetController()))
	{
		AIController->SetPatrolRoute(PatrolCharacterRoute);
		SetActorLocation(PatrolCharacterRoute->GetStartPosition());
	}
}

// Called when the game starts or when spawned
void APatrolCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (auto PatrolNpcSystem = GetWorld()->GetSubsystem<UPatrolNpcsSystem>())
	{
		PatrolNpcSystem->RegisterPatrolNpcActor(this);
	}
}

void APatrolCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	if(EndPlayReason != EEndPlayReason::Quit)
	{
		if (auto PatrolNpcSystem = GetWorld()->GetSubsystem<UPatrolNpcsSystem>())
		{
			PatrolNpcSystem->UnregisterPatrolNpcActor(this);
		}
	}
}

// Called every frame
void APatrolCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

