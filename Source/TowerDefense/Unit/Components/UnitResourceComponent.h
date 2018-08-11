// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UnitResourceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UUnitResourceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUnitResourceComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DefaultValues) int32 StartingResources = 1500;

private:
	int32 _currentResources;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	UFUNCTION() void ModifyResources(int32 resourceAmount);
};
