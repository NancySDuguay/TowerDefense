// Fill out your copyright notice in the Description page of Project Settings.

#include "UnitViewModel.h"
#include "TowerDefenseGameState.h"


void UUnitViewModel::BindUnit(ATowerDefenseCharacter* unit)
{
	_unit = unit;
	const auto gameState = GetWorld()->GetGameState<ATowerDefenseGameState>();
	gameState->GetEventManager()->OnGameOver.AddDynamic(this, &UUnitViewModel::OnGameOver);
}

int32 UUnitViewModel::GetResources() const
{
	if (auto const unitResourceComponent = _unit.Get()->GetUnitResourceComponent())
	{
		return unitResourceComponent->GetResourcesCount();
	}
	return 0;
}
