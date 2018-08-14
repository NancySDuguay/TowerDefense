// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerDefenseGameState.h"

ATowerDefenseGameState::ATowerDefenseGameState(): _eventManager(nullptr)
{
	_eventManager = CreateDefaultSubobject<UEventManager>(TEXT("Event Manager"));
}

void ATowerDefenseGameState::SetEnemyGoalLocation(FVector location)
{
	_enemyGoalLocation = location;
}
