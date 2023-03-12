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

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
	FProjectileInteractorDelegate OnProjectileHitDelegate;

	UFUNCTION(BlueprintCallable)
	virtual void OnProjectileHit(ARProjectile* Projectile, const FHitResult& Hit);
};
