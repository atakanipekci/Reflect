// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RProjectileInteractorComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FProjectileInteractorDelegate, class ARProjectile*, Projectile, const FHitResult&, Hit);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTREFLECT_API URProjectileInteractorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URProjectileInteractorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<class URProjectileBehaviorModifier*> BehaviorModifiers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnableBounce;

public:	
	UPROPERTY(BlueprintAssignable)
	FProjectileInteractorDelegate OnProjectileHitDelegate;

	UFUNCTION(BlueprintCallable)
	virtual void OnProjectileHit(ARProjectile* Projectile, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable)
	virtual FVector GetBounceDir(FVector Velocity, const FHitResult& Hit);
};
