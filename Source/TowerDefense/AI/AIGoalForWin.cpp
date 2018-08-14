// Fill out your copyright notice in the Description page of Project Settings.

#include "AIGoalForWin.h"
#include "TowerDefenseGameState.h"
#include "Engine/World.h"
#include <Components/StaticMeshComponent.h>
#include "EnemyUnit.h"


// Sets default values
AAIGoalForWin::AAIGoalForWin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	_root = CreateDefaultSubobject<USceneComponent>("root");
	RootComponent = _root;

	_goalTriggerBox = CreateDefaultSubobject<UBoxComponent>("Goal Trigger Box");
	_goalTriggerBox->SetupAttachment(RootComponent);
	_goalTriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	_goalTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AAIGoalForWin::OnOverlap);
}

void AAIGoalForWin::OnOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor,
	UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	if (otherActor->GetClass()->IsChildOf(AEnemyUnit::StaticClass())) {
		const auto gameState = GetWorld()->GetGameState<ATowerDefenseGameState>();
		gameState->GetEventManager()->OnGameOver.Broadcast();
	}
}

// Called when the game starts or when spawned
void AAIGoalForWin::BeginPlay()
{
	Super::BeginPlay();

	const auto gameState = GetWorld()->GetGameState<ATowerDefenseGameState>();
	gameState->SetEnemyGoalLocation(_goalTriggerBox->GetComponentLocation());
}
