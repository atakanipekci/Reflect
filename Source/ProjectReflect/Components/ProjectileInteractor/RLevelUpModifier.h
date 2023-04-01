// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RProjectileBehaviorModifier.h"
#include "RLevelUpModifier.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTREFLECT_API URLevelUpModifier : public URProjectileBehaviorModifier
{
	GENERATED_BODY()
public:
	virtual void ApplyBehavior(ARProjectile* Projectile, const FHitResult& Hit) override;

	UPROPERTY(EditAnywhere)
	int LevelIncrease = 1;
};
