// Fill out your copyright notice in the Description page of Project Settings.

#include "UnitViewModel.h"


void UUnitViewModel::BindUnit(ATowerDefenseCharacter* unit)
{
	_unit = unit;
}

int32 UUnitViewModel::GetResources() const
{
	if (auto const unitResourceComponent = _unit.Get()->GetUnitResourceComponent())
	{
		return unitResourceComponent->GetResourcesCount();
	}
	return 0;
}
