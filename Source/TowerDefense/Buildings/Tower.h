// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tower.generated.h"

UCLASS()
class TOWERDEFENSE_API ATower : public AActor
{
	GENERATED_BODY()

	TArray<TWeakObjectPtr<AActor>> _enemiesInRange;

public:	
	// Sets default values for this actor's properties
	ATower();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=thing) USceneComponent* Root;
	/** location used to spawn the turret */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=thing) USceneComponent* LazerSpawnLocation;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
