// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RProjectile.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FProjectileHitSignature, AActor*, OtherActor, const FHitResult&, Hit);
UCLASS()
class PROJECTREFLECT_API ARProjectile : public AActor
{
	GENERATED_BODY()

protected:
	ARProjectile();

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	virtual void DestroyProjectile();
	
	UPROPERTY(VisibleDefaultsOnly, Category = Collision)
	class USphereComponent* InnerCollision;

	// UPROPERTY(VisibleDefaultsOnly, Category = Collision)
	// class USphereComponent* OuterCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	class UProjectileMovementComponent* ProjectileMovement;

	int CurrentHitCount;
	

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Projectile)
	int HitCountToDestroy;

	UPROPERTY(BlueprintCallable, Category = Projectile)
	FProjectileHitSignature OnProjectileHit;
};
