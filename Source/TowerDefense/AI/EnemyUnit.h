// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Unit/Components/UnitHealthComponent.h"
#include "EnemyUnit.generated.h"

UCLASS(Blueprintable, BlueprintType)
class TOWERDEFENSE_API AEnemyUnit : public ACharacter
{
	GENERATED_BODY()

	UUnitHealthComponent* _unitHealthComponent;
public:
	AEnemyUnit();

	/** the resource count the player will get if they kill an enemy. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere) int32 RewardResources = 100;
	
	UFUNCTION(BlueprintCallable, Category=Components) UUnitHealthComponent* GetUnitComponent() const { return _unitHealthComponent; }
	
	UFUNCTION() void OnDeath();

protected:
	void BeginPlay() override;
};
