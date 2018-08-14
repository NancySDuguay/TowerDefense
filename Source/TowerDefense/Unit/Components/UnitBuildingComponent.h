// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnitResourceComponent.h"
#include "Buildings/DefenseTowerSpawn.h"
#include "Buildings/Tower.h"
#include "UnitBuildingComponent.generated.h"

/** This component takes care of building towers */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UUnitBuildingComponent : public UActorComponent
{
	GENERATED_BODY()

	TArray<TWeakObjectPtr<ADefenseTowerSpawn>> _potentialSpawnPoints;
	TWeakObjectPtr<UUnitResourceComponent> _unitResourceComponent;
	TSubclassOf<ATower> _towerClass;

public:	
	// Sets default values for this component's properties
	UUnitBuildingComponent();
	void BuildTower();
	ADefenseTowerSpawn* GetSpawnPointLocationClosestToPlayerView();

	// add and remove from potential tower spawn points.
	UFUNCTION(BlueprintCallable) void AddToPotentialSpawnPoints(ADefenseTowerSpawn* potentialSpawnPoint);
	UFUNCTION(BlueprintCallable) void RemoveFromPotentialSpawnPoints(ADefenseTowerSpawn* potentialSpawnPointToRemove);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;		
	
};

