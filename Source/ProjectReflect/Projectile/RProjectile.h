// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "RProjectile.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FProjectileHitDelegate, AActor*, OtherActor, const FHitResult&, Hit);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FProjectileBounceDelegate, class URProjectileInteractorComponent*,LastHitInteractorComponent, AActor*, HitActor,const FHitResult&, ImpactResult, const FVector&, ImpactVelocity);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FProjectileStopDelegate, const FHitResult&, ImpactResult);

UCLASS()
class PROJECTREFLECT_API ARProjectile : public AActor
{
	GENERATED_BODY()

protected:
	ARProjectile();
	void TryInvokeInteractorComponent(class URProjectileInteractorComponent* OtherActor, const FHitResult& Hit);

	URProjectileInteractorComponent* GetInteractorComponentFromActor(const AActor* OtherActor) const;
	
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	virtual void OnBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity);
	UFUNCTION()
	virtual void OnStop(const FHitResult& ImpactResult);

	UFUNCTION()
	void OnLevelUp(int OldLevel, int NewLevel);

	UPROPERTY(VisibleDefaultsOnly, Category = Collision)
	class USphereComponent* InnerCollision;

	UPROPERTY(EditAnywhere)
	class URDamageComponent* DamageComponent;

	

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

	UPROPERTY(EditAnywhere)
	class URLevelComponent* LevelComponent;
	
	UPROPERTY()
	URProjectileInteractorComponent* LastHitInteractorComponent;
	UPROPERTY()
	AActor* LastHitActor;

	UFUNCTION()
	UProjectileMovementComponent* GetProjectileMovementComponent() const;

	UFUNCTION()
	virtual void DestroyProjectile();

	UFUNCTION()
	float GetRadius();
};
