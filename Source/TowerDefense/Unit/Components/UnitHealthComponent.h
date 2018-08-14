// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnitHealthComponent.generated.h"

/** This component takes care of the unit's health */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UUnitHealthComponent : public UActorComponent
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathEvent);

	float _currentHealth;

public:
	UUnitHealthComponent();

	UPROPERTY(BlueprintReadWrite, EditAnywhere) float StartingHealth = 200.f;
	
	UPROPERTY(BlueprintAssignable) FDeathEvent OnDeath;

	UFUNCTION(BlueprintCallable) void TakeDamage(float damage);
	

};
