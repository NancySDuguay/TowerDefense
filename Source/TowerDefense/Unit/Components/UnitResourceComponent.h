// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnitResourceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UUnitResourceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UUnitResourceComponent();
	bool CanSpendResource(int32 resourceNeeded) const { return _currentResources >= resourceNeeded; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DefaultValues) int32 StartingResources = 1500;

private:
	int32 _currentResources;

protected:
	virtual void BeginPlay() override;

public:	
	int32 GetResourcesCount() const { return _currentResources; }
	UFUNCTION() void ModifyResources(int32 resourceAmount);
};
