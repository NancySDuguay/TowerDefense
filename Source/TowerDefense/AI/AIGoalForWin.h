// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "AIGoalForWin.generated.h"

UCLASS()
class TOWERDEFENSE_API AAIGoalForWin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAIGoalForWin();

	UPROPERTY(VisibleAnywhere) USceneComponent* _root;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) UBoxComponent* _goalTriggerBox;
	UFUNCTION() void OnOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult & sweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
