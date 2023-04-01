// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RProjectileBehaviorModifier.h"
#include "RBounceBehaviorModifierComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTREFLECT_API URBounceBehaviorModifierComponent : public URProjectileBehaviorModifier
{
	GENERATED_BODY()

public:	
	URBounceBehaviorModifierComponent();

	virtual void ApplyBehavior(ARProjectile* Projectile, const FHitResult& Hit) override;
	virtual FVector GetBounceDir(FVector Velocity, const FHitResult& Hit) override;

	UPROPERTY(EditAnywhere, Category = Properties)
	bool bModifyGravityOnHit;
	
	UPROPERTY(EditAnywhere, Category = Properties)
	float Gravity;
	
	UPROPERTY(EditAnywhere, Category = Properties)
	bool StopMovementImmediately;

	
};
