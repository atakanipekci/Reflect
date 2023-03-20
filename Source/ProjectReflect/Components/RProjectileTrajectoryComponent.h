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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SpawnTrajectorySpline();
	void DrawSpline(TArray<FVector> Path);
	void DrawTrajectory(FVector Origin, FVector ShootDir, ARProjectile* ProjectileBp, TArray<TObjectPtr<AActor>> ActorsToIgnore, const FVector& MuzzleLocation, const FRotator& MuzzleRotation);
	void ClearTrajectory();
	FPredictProjectilePathParams GetMainTrajectoryParams(FVector StartLocation, FVector Velocity, float Radius, TArray<TObjectPtr<AActor>> ActorsToIgnore, float Gravity);
	FPredictProjectilePathParams GetMuzzleTrajectoryParams(FVector EndLocation, FVector MuzzleLocation, FRotator MuzzleRotation, float Radius, TArray<TObjectPtr<AActor>> ActorsToIgnore, float Gravity);

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ARSplineActor> TrajectorySplineBP;
	
	UPROPERTY()
	ARSplineActor* TrajectorySplineInstance;
	UPROPERTY()
	ARSplineActor* TrajectoryReflectionSplineInstance;
	
		
};
