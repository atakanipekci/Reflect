// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RProjectileBehaviorModifier.h"
#include "RProjectileDestroyerComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTREFLECT_API URProjectileDestroyerComponent : public URProjectileBehaviorModifier
{
	GENERATED_BODY()
	virtual void ApplyBehavior(ARProjectile* Projectile, const FHitResult& Hit) override;
};
