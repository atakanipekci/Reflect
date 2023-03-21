// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectReflect/Projectile/RProjectile.h"
#include "RProjectileTrajectoryComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTREFLECT_API URProjectileTrajectoryComponent : public UActorComponent
{
	GENERATED_BODY()

	URProjectileTrajectoryComponent();

public:
	
	void SpawnTrajectorySpline();
	void DrawTrajectorySplineFromWeapon(TArray<FVector> Path) const;
	void DrawTrajectorySplineFromReflection(TArray<FVector> Path) const;
	void DrawTrajectory(FVector Origin, FVector ShootDir, ARProjectile* ProjectileBp, TArray<TObjectPtr<AActor>> ActorsToIgnore, const FVector& MuzzleLocation, const FRotator& MuzzleRotation);
	void ClearTrajectory();
	void DisableSplineFromWeapon() const;
	void DisableSplineFromReflection() const;
	FPredictProjectilePathParams GetTrajectoryParams(FVector StartLocation, FVector Velocity, float Radius, TArray<TObjectPtr<AActor>> ActorsToIgnore, float Gravity, float SimTime);

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ARSplineActor> TrajectorySplineBP;
	
	UPROPERTY()
	ARSplineActor* TrajectorySplineInstance;
	UPROPERTY()
	ARSplineActor* TrajectoryReflectionSplineInstance;
};
