// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerDefenseProjectile.h"
#include "Tower.generated.h"

class ACharacter;
class USphereComponent;

/** The tower which will shoot at any enemy close to it at a certain firerate. */
UCLASS()
class TOWERDEFENSE_API ATower : public AActor
{
	GENERATED_BODY()

	TArray<TWeakObjectPtr<ACharacter>> _enemiesInRange;

public:	
	// Sets default values for this actor's properties
	ATower();
	
	virtual void Tick(float DeltaTime) override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) USceneComponent* Root;
	/** location used to spawn the turret */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) USceneComponent* LazerSpawnLocation;
	/** shape that rotates to where the turret is looking at */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) UStaticMeshComponent* Muzzle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) USphereComponent* TowerRange;
	/** how many bullets the turrets will shoot per minute */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Fire) float FireRate = 180.f;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<ATowerDefenseProjectile> ProjectileClass;

private:
	void FireAtEnemy(FVector EnemyLocation) const;
	float _coolDownBetweenBullets;
	bool _isOnCooldown;

	UFUNCTION()	void OnOverlapBegin(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool
	           	                    bFromSweep, const FHitResult& sweepResult);
	UFUNCTION()	void OnOverlapEnd(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp,
	           	                  int32 otherBodyIndex);
	UFUNCTION() void EndCooldown();
};
