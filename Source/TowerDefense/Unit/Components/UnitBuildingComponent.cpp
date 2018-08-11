// Fill out your copyright notice in the Description page of Project Settings.

#include "UnitBuildingComponent.h"
#include <ConstructorHelpers.h>
#include <Engine/World.h>


// Sets default values for this component's properties
UUnitBuildingComponent::UUnitBuildingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	

	static ConstructorHelpers::FClassFinder<ATower> TowerClass(TEXT("Blueprint'/Game/Buildings/BP_TowerSmall.BP_TowerSmall_C'"));
	if (TowerClass.Succeeded())
	{
		_towerClass = TowerClass.Class;
	}

	// ...
}

void UUnitBuildingComponent::BuildTower()
{
	// Return if there's no potential tower spawn points.
	if (_potentialSpawnPoints.Num() == 0) return;
	// check if there's enough resources
	if (_unitResourceComponent->CanSpendResource(500))
	{
		auto const spawnPoint = GetSpawnPointLocationClosestToPlayerView();
		GetOwner()->GetWorld()->SpawnActor<ATower>(_towerClass, spawnPoint->GetSpawnLocation(), spawnPoint->GetSpawnRotation());
		RemoveFromPotentialSpawnPoints(spawnPoint);
		spawnPoint->Destroy();
		_unitResourceComponent->ModifyResources(-500);
	}
}

// todo: this needs some love
/** Get the spawn point closest to the player, this one will spawn a tower */
ADefenseTowerSpawn* UUnitBuildingComponent::GetSpawnPointLocationClosestToPlayerView()
{
	const auto playerPosition = GetOwner()->GetActorLocation();
	const auto playerForwardVector = GetOwner()->GetActorForwardVector();

	if (_potentialSpawnPoints.Num() == 1) return _potentialSpawnPoints[0].Get();
	auto smallestAngle = acosf(FVector::DotProduct(_potentialSpawnPoints[0].Get()->GetSpawnLocation()-playerPosition, playerForwardVector));
		FVector::Dist(_potentialSpawnPoints[0].Get()->GetSpawnLocation(), playerPosition);
	auto bestSpawnPoint = _potentialSpawnPoints[0];

	for (auto i = 1; i < _potentialSpawnPoints.Num(); i++)
	{
		auto const angleSpawnPointToUnit = acosf(FVector::DotProduct(_potentialSpawnPoints[i].Get()->GetSpawnLocation()-playerPosition, playerForwardVector));
		if (angleSpawnPointToUnit < smallestAngle)
		{
			smallestAngle = angleSpawnPointToUnit;
			bestSpawnPoint = _potentialSpawnPoints[i];
		}
	}
	return bestSpawnPoint.Get();
}

void UUnitBuildingComponent::AddToPotentialSpawnPoints(ADefenseTowerSpawn* potentialSpawnPoint)
{
	if (!IsValid(potentialSpawnPoint)) return;
	_potentialSpawnPoints.Add(potentialSpawnPoint);
}

void UUnitBuildingComponent::RemoveFromPotentialSpawnPoints(ADefenseTowerSpawn* potentialSpawnPointToRemove)
{
	_potentialSpawnPoints.Remove(potentialSpawnPointToRemove);
	_potentialSpawnPoints.Shrink();
}


// Called when the game starts
void UUnitBuildingComponent::BeginPlay()
{
	Super::BeginPlay();

	_unitResourceComponent = GetOwner()->FindComponentByClass<UUnitResourceComponent>();
	// ...
	
}


// Called every frame
void UUnitBuildingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

