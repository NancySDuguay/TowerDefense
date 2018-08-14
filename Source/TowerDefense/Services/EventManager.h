// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EventManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Category = "Global Evenets" )
class TOWERDEFENSE_API UEventManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEventManager();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeathEvent, int32, moneyAmount);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameplayEvent);

	UPROPERTY(BlueprintAssignable, Category = "Resource event")
	FDeathEvent OnEnemyDeath;

	
	UPROPERTY(BlueprintAssignable, Category = "Gameplay event")
	FGameplayEvent OnGameOver;

	UPROPERTY(BlueprintAssignable, Category = "Gameplay event")
	FGameplayEvent TriedToOverSpend;
};
