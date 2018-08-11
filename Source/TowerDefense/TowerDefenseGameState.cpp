// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerDefenseGameState.h"

ATowerDefenseGameState::ATowerDefenseGameState(): EventManager(nullptr)
{
	EventManager = CreateDefaultSubobject<UEventManager>(TEXT("Event Manager"));
}