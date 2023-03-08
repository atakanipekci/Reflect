// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectReflect/Projectile/RProjectile.h"
#include "RAcceleratingProjectile.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTREFLECT_API ARAcceleratingProjectile : public ARProjectile
{
	GENERATED_BODY()

protected:
	ARAcceleratingProjectile();

	UPROPERTY(EditAnywhere, Category = Projectile)
	float SpeedBoostOnBounce;

	virtual void OnBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity) override;
};
