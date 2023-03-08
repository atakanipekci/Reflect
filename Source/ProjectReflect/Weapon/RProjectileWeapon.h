// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RWeapon.h"
#include "RProjectileWeapon.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTREFLECT_API ARProjectileWeapon : public ARWeapon
{
	GENERATED_BODY()
	
public:
	virtual void Fire() override;

	UFUNCTION()
	virtual void SpawnProjectile() const;

	UFUNCTION()
	void OnProjectileHit(AActor* OtherActor, const FHitResult& Hit);

	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class ARProjectile> ProjectileClass;
};
