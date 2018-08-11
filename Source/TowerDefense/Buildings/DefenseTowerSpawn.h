// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DefenseTowerSpawn.generated.h"

UCLASS()
class TOWERDEFENSE_API ADefenseTowerSpawn : public AActor
{
	GENERATED_BODY()
	
public:
	ADefenseTowerSpawn();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=thing) USceneComponent* Root;

	/** location used to spawn the turret */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=thing) USceneComponent* SpawnLocation;

	FVector GetSpawnLocation() const;
	// Sets default values for this actor's properties

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	
};
