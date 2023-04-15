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
	
	UFUNCTION()
	virtual void SpawnProjectile(FVector Location, FRotator Rotation);

	void CreateDecal(AActor* Actor, const FHitResult& Hit);
	UFUNCTION()
	void OnProjectileHit(AActor* OtherActor, const FHitResult& Hit);

	virtual void Shoot(FVector Location, FRotator Rotation) override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	void DrawTrajectory(FVector SpawnPos, FVector Dir, TArray<TObjectPtr<AActor>> ActorsToIgnore) const;

	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class ARProjectile> ProjectileClass;
	
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	class UMaterialInterface* DecalMaterial;

	UPROPERTY()
	class URProjectileTrajectoryComponent* TrajectoryComponent;

	UPROPERTY()
	class ARProjectile* LastFiredProjectile = nullptr;
};
