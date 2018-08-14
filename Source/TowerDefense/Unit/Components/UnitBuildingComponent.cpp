// Fill out your copyright notice in the Description page of Project Settings.

#include "UnitBuildingComponent.h"
#include "ConstructorHelpers.h"
#include "TowerDefenseGameState.h"


UUnitBuildingComponent::UUnitBuildingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	// load the tower class.
	static ConstructorHelpers::FClassFinder<ATower> TowerClass(TEXT("Blueprint'/Game/Buildings/BP_TowerSmall.BP_TowerSmall_C'"));
	if (TowerClass.Succeeded())
	{
		_towerClass = TowerClass.Class;
	}
}

void UUnitBuildingComponent::BuildTower()
{
	// Return if there's no potential tower spawn points.
	if (_potentialSpawnPoints.Num() == 0) return;
	// check if there's enough resources to build a tower
	if (_unitResourceComponent->CanSpendResource(500))
	{
		auto const spawnPoint = GetSpawnPointLocationClosestToPlayerView();
		GetOwner()->GetWorld()->SpawnActor<ATower>(_towerClass, spawnPoint->GetSpawnLocation(), spawnPoint->GetSpawnRotation());
		RemoveFromPotentialSpawnPoints(spawnPoint);
		spawnPoint->Destroy();
		_unitResourceComponent->ModifyResources(-500);
	} 
	else // if there's not enough resources, event so that the UI can show an indication of why building didn't work.
	{
		const auto gameState = GetWorld()->GetGameState<ATowerDefenseGameState>();
		gameState->GetEventManager()->TriedToOverSpend.Broadcast();
	}
}

/** Get the tower spawn point closest to where the player is looking at */
ADefenseTowerSpawn* UUnitBuildingComponent::GetSpawnPointLocationClosestToPlayerView()
{
	const auto playerPosition = GetOwner()->GetActorLocation();
	const auto playerForwardVector = GetOwner()->GetActorForwardVector();

	// if there's only one potential spawn point, return that one
	if (_potentialSpawnPoints.Num() == 1) return _potentialSpawnPoints[0].Get();

	// get the spawn point with the lowest angle with the character's forward vector
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
}