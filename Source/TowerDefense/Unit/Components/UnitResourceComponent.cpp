// Fill out your copyright notice in the Description page of Project Settings.

#include "UnitResourceComponent.h"


// Sets default values for this component's properties
UUnitResourceComponent::UUnitResourceComponent(): _currentResources(0)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UUnitResourceComponent::BeginPlay()
{
	Super::BeginPlay();

	_currentResources = StartingResources;
	// ...
	
}

void UUnitResourceComponent::ModifyResources(int32 resourceAmount)
{
	_currentResources += resourceAmount;
}

