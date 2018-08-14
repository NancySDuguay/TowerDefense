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

public:
	UPROPERTY(BlueprintReadOnly, Category = "Events") UEventManager* EventManager;

	UFUNCTION(BlueprintCallable) UEventManager* GetEventManager() const { return EventManager; }

	
	void SetEnemyGoalLocation(FVector location);
	UFUNCTION(BlueprintCallable) FVector GetEnemyGoalLocation() const { return _enemyGoalLocation; }
};
