// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TowerDefenseCharacter.h"
#include "UnitViewModel.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UUnitViewModel : public UUserWidget
{
	GENERATED_BODY()
	
	TWeakObjectPtr<ATowerDefenseCharacter> _unit = nullptr;

public:
	UFUNCTION(BlueprintCallable, Category=Resources) void BindUnit(ATowerDefenseCharacter* unit);
	UFUNCTION(BlueprintImplementableEvent) void OnGameOver();
	UFUNCTION(BlueprintImplementableEvent) void OnTriedToOverspend();
	UFUNCTION(BlueprintCallable, Category=Resources) int32 GetResources() const;
};
