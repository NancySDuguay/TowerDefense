// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "TowerDefenseProjectile.h"
#include "Tower.generated.h"

class ACharacter;

UCLASS()
class TOWERDEFENSE_API ATower : public AActor
{
	GENERATED_BODY()

	TArray<TWeakObjectPtr<ACharacter>> _enemiesInRange;

public:	
	// Sets default values for this actor's properties
	ATower();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) USceneComponent* Root;
	/** location used to spawn the turret */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) USceneComponent* LazerSpawnLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) USphereComponent* TowerRange;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Fire) float FireRate = 180; // default to 3 bullets per second.

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<ATowerDefenseProjectile> ProjectileClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()	void OnOverlapBegin(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool
	           	                    bFromSweep, const FHitResult& sweepResult);
	UFUNCTION()	void OnOverlapEnd(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp,
	           	                  int32 otherBodyIndex);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	UFUNCTION() void EndCooldown();

private:
	void FireAtEnemy(FVector EnemyLocation) const;
	float _coolDownBetweenBullets;
	bool _isOnCooldown;
};
