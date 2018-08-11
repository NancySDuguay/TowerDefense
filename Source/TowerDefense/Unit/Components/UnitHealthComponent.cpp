// Fill out your copyright notice in the Description page of Project Settings.

#include "UnitHealthComponent.h"
#include "UnitResourceComponent.h"


// Sets default values for this component's properties
UUnitHealthComponent::UUnitHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	_currentHealth = StartingHealth;
	// ...
}


void UUnitHealthComponent::TakeDamage(float damage)
{
	_currentHealth -= damage;
	if (_currentHealth <= 0.f)
	{
		OnDeath.Broadcast();
	}
}

// Called when the game starts
void UUnitHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UUnitHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

