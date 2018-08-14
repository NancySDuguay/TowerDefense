// Fill out your copyright notice in the Description page of Project Settings.

#include "UnitResourceComponent.h"


UUnitResourceComponent::UUnitResourceComponent(): _currentResources(0)
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UUnitResourceComponent::BeginPlay()
{
	Super::BeginPlay();

	_currentResources = StartingResources;
	
}

void UUnitResourceComponent::ModifyResources(int32 resourceAmount)
{
	_currentResources += resourceAmount;
}

