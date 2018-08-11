// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UnitHealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UUnitHealthComponent : public UActorComponent
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathEvent);
public:
	UPROPERTY(BlueprintAssignable) FDeathEvent OnDeath;
	// Sets default values for this component's properties
	UUnitHealthComponent();

	UPROPERTY(BlueprintReadWrite, EditAnywhere) float StartingHealth = 200.f;
	UFUNCTION(BlueprintCallable) void TakeDamage(float damage);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float _currentHealth;
		
	
};
