// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyUnit.h"
#include "TowerDefenseGameState.h"
#include <Engine/World.h>


// Sets default values
AEnemyUnit::AEnemyUnit()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_unitHealthComponent = CreateDefaultSubobject<UUnitHealthComponent>(TEXT("Health Component"));

}

// Called when the game starts or when spawned
void AEnemyUnit::BeginPlay()
{
	Super::BeginPlay();

	_unitHealthComponent->OnDeath.AddDynamic(this, &AEnemyUnit::OnDeath);
}

void AEnemyUnit::OnDeath()
{
	const auto gameState = GetWorld()->GetGameState<ATowerDefenseGameState>();
	gameState->EventManager->OnEnemyDeath.Broadcast(RewardResources);
	Destroy();
}

// Called every frame
void AEnemyUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
