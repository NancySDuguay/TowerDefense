// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Services/EventManager.h"
#include "TowerDefenseGameState.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATowerDefenseGameState : public AGameStateBase
{
	GENERATED_BODY()

	ATowerDefenseGameState();

	FVector _enemyGoalLocation = FVector::ZeroVector;
	UEventManager* _eventManager;

public:
	// todo: Make a function library and call this function from there, since it'll be used often
	UFUNCTION(BlueprintCallable) UEventManager* GetEventManager() const { return _eventManager; }

	void SetEnemyGoalLocation(FVector location);
	UFUNCTION(BlueprintCallable) FVector GetEnemyGoalLocation() const { return _enemyGoalLocation; }
};
