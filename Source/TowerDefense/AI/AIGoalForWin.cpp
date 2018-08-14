// Fill out your copyright notice in the Description page of Project Settings.

#include "AIGoalForWin.h"
#include "TowerDefenseGameState.h"
#include "Components/BoxComponent.h"
#include "EnemyUnit.h"


AAIGoalForWin::AAIGoalForWin()
{
	PrimaryActorTick.bCanEverTick = false;

	_root = CreateDefaultSubobject<USceneComponent>("root");
	RootComponent = _root;

	_goalTriggerBox = CreateDefaultSubobject<UBoxComponent>("Goal Trigger Box");
	_goalTriggerBox->SetupAttachment(RootComponent);
	_goalTriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	_goalTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AAIGoalForWin::OnOverlap);
}

// when the enemy overlaps the goal trigger, it's game over
void AAIGoalForWin::OnOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor,
	UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	if (otherActor->GetClass()->IsChildOf(AEnemyUnit::StaticClass())) {
		const auto gameState = GetWorld()->GetGameState<ATowerDefenseGameState>();
		gameState->GetEventManager()->OnGameOver.Broadcast();
	}
}

void AAIGoalForWin::BeginPlay()
{
	Super::BeginPlay();

	// Set the enemy goal location in the game state so that it can be accessed by all
	const auto gameState = GetWorld()->GetGameState<ATowerDefenseGameState>();
	gameState->SetEnemyGoalLocation(_goalTriggerBox->GetComponentLocation());
}
