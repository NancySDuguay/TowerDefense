// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tower.h"
#include "DefenseTowerSpawn.generated.h"

UCLASS()
class TOWERDEFENSE_API ADefenseTowerSpawn : public AActor
{
	GENERATED_BODY()
	
public:
	ADefenseTowerSpawn();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=thing) USceneComponent* Root;
	
	/** location used for spawning the turret */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=thing) USceneComponent* SpawnLocation;

	FVector GetSpawnLocation() const;
	FRotator GetSpawnRotation() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	
};
