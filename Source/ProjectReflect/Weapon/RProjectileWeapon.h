// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RWeapon.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "RProjectileWeapon.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTREFLECT_API ARProjectileWeapon : public ARWeapon
{
	GENERATED_BODY()
	
public:
	ARProjectileWeapon();
	
	virtual void Fire() override;
	FRotator GetProjectileSpawnRotation() const;
	FVector GetProjectileSpawnLocation(FRotator SpawnRotation) const;

	UFUNCTION()
	virtual void SpawnProjectile() const;

	
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnProjectileHit(AActor* OtherActor, const FHitResult& Hit);

	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class ARProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class URProjectileTrajectoryComponent* TrajectoryComponent;
};
