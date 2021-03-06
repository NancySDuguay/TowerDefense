// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"
#include "AI/EnemyUnit.h"
#include "Kismet/KismetMathLibrary.h"
#include "TowerDefenseGameState.h"
#include "Components/SphereComponent.h"

ATower::ATower()
{
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickEnabled(false);

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	LazerSpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Lazer Location"));
	LazerSpawnLocation->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	TowerRange = CreateDefaultSubobject<USphereComponent>(TEXT("Range"));
	TowerRange->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	Muzzle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Muzzle"));
	Muzzle->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	Muzzle->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	TowerRange->OnComponentBeginOverlap.AddDynamic(this, &ATower::OnOverlapBegin);
	TowerRange->OnComponentEndOverlap.AddDynamic(this, &ATower::OnOverlapEnd);

	_coolDownBetweenBullets = 60.f / FireRate; // 60 seconds in a minute, hence the "magic" number
	_isOnCooldown = false;
}

void ATower::OnOverlapBegin(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult & sweepResult)
{
	if (const auto enemy = Cast<AEnemyUnit>(otherActor)) // see if the overlapped actor is an enemy. todo: would be nice to have team interface working, so we wouldn't need the dependency of AEnemyUnit
	{
		_enemiesInRange.Add(enemy);
		if (_enemiesInRange.Num() == 1) SetActorTickEnabled(true);
	}
}

void ATower::OnOverlapEnd(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex)
{
	if (_enemiesInRange.Contains(otherActor))
	{
		_enemiesInRange.Remove(Cast<ACharacter>(otherActor)); 
		if (_enemiesInRange.Num() == 0)
		{
			SetActorTickEnabled(false); // No need to tick if there's no enemies around
		}
	}
}

void ATower::FireAtEnemy(FVector EnemyLocation) const
{
	// try and fire a projectile
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			const auto spawnRotation = UKismetMathLibrary::FindLookAtRotation(LazerSpawnLocation->GetComponentLocation(), EnemyLocation);
			Muzzle->SetWorldRotation(spawnRotation);
			World->SpawnActor<ATowerDefenseProjectile>(ProjectileClass, LazerSpawnLocation->GetComponentLocation(), spawnRotation);
		}
	}
}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_isOnCooldown) return;

	// check if any of the entries are dead enemies
	_enemiesInRange.RemoveAllSwap([](TWeakObjectPtr<ACharacter> unit) { return !IsValid(unit.Get()); }); // remove invalid enemies (they've been killed).
	if (_enemiesInRange.Num() == 0)
	{
		SetActorTickEnabled(false); // No need to tick if there's no enemies around
		return;
	}

	// sort by distance of the goal
	const auto gameState = GetWorld()->GetGameState<ATowerDefenseGameState>();
	auto const goalLocation = gameState->GetEnemyGoalLocation();
	_enemiesInRange.Sort([goalLocation](TWeakObjectPtr<ACharacter> unitA, TWeakObjectPtr<ACharacter> unitB)
	{
		return FVector::Dist(unitA->GetActorLocation(), goalLocation) > FVector::Dist(unitB->GetActorLocation(), goalLocation);
	});

	const auto towerLocation = LazerSpawnLocation->GetComponentLocation();
	for (const auto& enemy : _enemiesInRange)
	{
		const auto enemyLocation = enemy->GetMesh()->GetBoneLocation("spine_03");
		// check if enemy can be shot at.
		FHitResult OutHit;
		GetWorld()->LineTraceSingleByChannel(OutHit, towerLocation, enemyLocation, ECollisionChannel::ECC_Pawn);
		if (OutHit.Actor == enemy)
		{
			FireAtEnemy(enemyLocation);
			_isOnCooldown = true;
			FTimerHandle cooldownTimerHandle;
			GetWorld()->GetTimerManager().SetTimer(cooldownTimerHandle, this, &ATower::EndCooldown, _coolDownBetweenBullets, false);
			return; // stop looking for an enemy to shoot at since we found one.
		}
	}
}

void ATower::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// clearing the cooldown timer.
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	Super::EndPlay(EndPlayReason);
}

void ATower::EndCooldown()
{
	_isOnCooldown = false;
}

