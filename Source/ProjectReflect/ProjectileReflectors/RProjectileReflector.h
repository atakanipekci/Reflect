// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectReflect/Projectile/RProjectile.h"
#include "RProjectileReflector.generated.h"

UCLASS()
class PROJECTREFLECT_API ARProjectileReflector : public AActor
{
	GENERATED_BODY()
	
public:
	ARProjectileReflector();

	UFUNCTION()
	virtual void OnProjectileHit(ARProjectile* Projectile, const FHitResult& Hit);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class URProjectileInteractorComponent* ProjectileInteractionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* StaticMeshComponent; 
};
