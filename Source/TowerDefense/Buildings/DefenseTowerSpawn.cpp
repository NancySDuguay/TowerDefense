// Fill out your copyright notice in the Description page of Project Settings.

#include "DefenseTowerSpawn.h"


// Sets default values
ADefenseTowerSpawn::ADefenseTowerSpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Location"));
	SpawnLocation->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

}

FVector ADefenseTowerSpawn::GetSpawnLocation() const
{
	return SpawnLocation->GetComponentLocation();
}

FRotator ADefenseTowerSpawn::GetSpawnRotation() const
{
	return SpawnLocation->GetComponentRotation();
}

// Called when the game starts or when spawned
void ADefenseTowerSpawn::BeginPlay()
{
	Super::BeginPlay();
	
}

