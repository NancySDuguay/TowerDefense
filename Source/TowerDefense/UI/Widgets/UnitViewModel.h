// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerDefenseCharacter.h"
#include "UserWidget.h"
#include "UnitViewModel.generated.h"

/** Viewmodel for hooking up to game events and getting the user's resources */
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
