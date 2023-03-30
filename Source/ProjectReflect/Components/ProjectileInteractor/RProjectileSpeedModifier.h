// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RProjectileBehaviorModifier.h"
#include "RProjectileSpeedModifier.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTREFLECT_API URProjectileSpeedModifier : public URProjectileBehaviorModifier
{
	GENERATED_BODY()
public:

	virtual void ApplyBehavior(ARProjectile* Projectile, const FHitResult& Hit) override;
	
	UPROPERTY(EditAnywhere)
	float SpeedMultiplier = 1.0f;
};
