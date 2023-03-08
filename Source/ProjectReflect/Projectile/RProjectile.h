// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RProjectile.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FProjectileHitDelegate, AActor*, OtherActor, const FHitResult&, Hit);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FProjectileBounceDelegate, const FHitResult&, ImpactResult, const FVector&, ImpactVelocity);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FProjectileStopDelegate, const FHitResult&, ImpactResult);

UCLASS()
class PROJECTREFLECT_API ARProjectile : public AActor
{
	GENERATED_BODY()

protected:
	ARProjectile();

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	virtual void OnBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity);
	UFUNCTION()
	virtual void OnStop(const FHitResult& ImpactResult);
	UFUNCTION()
	virtual void DestroyProjectile();
	
	UPROPERTY(VisibleDefaultsOnly, Category = Collision)
	class USphereComponent* InnerCollision;

	// UPROPERTY(VisibleDefaultsOnly, Category = Collision)
	// class USphereComponent* OuterCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	class UProjectileMovementComponent* ProjectileMovement;

	int CurrentBounceCount;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Projectile)
	int BounceCountToDestroy;

	UPROPERTY(BlueprintCallable, Category = Projectile)
	FProjectileHitDelegate OnProjectileHit;

	UPROPERTY(BlueprintAssignable)
	FProjectileBounceDelegate OnProjectileBounce;

	UPROPERTY(BlueprintAssignable)
	FProjectileStopDelegate OnProjectileStop;
};
