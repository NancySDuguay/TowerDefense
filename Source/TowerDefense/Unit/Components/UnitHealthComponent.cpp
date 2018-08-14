// Fill out your copyright notice in the Description page of Project Settings.

#include "UnitHealthComponent.h"


// Sets default values for this component's properties
UUnitHealthComponent::UUnitHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	_currentHealth = StartingHealth;
}


void UUnitHealthComponent::TakeDamage(float damage)
{
	_currentHealth -= damage;
	if (_currentHealth <= 0.f)
	{
		OnDeath.Broadcast();
	}
}


