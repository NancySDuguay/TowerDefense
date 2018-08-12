// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Unit/Components/UnitHealthComponent.h"
#include "EnemyUnit.generated.h"

UCLASS()
class TOWERDEFENSE_API AEnemyUnit : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyUnit();

	UPROPERTY(BlueprintReadWrite, EditAnywhere) int32 RewardResources = 100;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UUnitHealthComponent* _unitHealthComponent;

public:
	UFUNCTION(BlueprintCallable, Category=Components) UUnitHealthComponent* GetUnitComponent() const { return _unitHealthComponent; }
	UFUNCTION() void OnDeath();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
};
