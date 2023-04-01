// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "RProjectileBehaviorModifier.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTREFLECT_API URProjectileBehaviorModifier : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	virtual void ApplyBehavior(class ARProjectile* Projectile, const FHitResult& Hit);
	
	UFUNCTION(BlueprintCallable)
	virtual FVector GetBounceDir(FVector Velocity, const FHitResult& Hit);
};
