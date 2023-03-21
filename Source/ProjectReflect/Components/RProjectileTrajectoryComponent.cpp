// Fill out your copyright notice in the Description page of Project Settings.


#include "RProjectileTrajectoryComponent.h"

#include "Kismet/GameplayStatics.h"
#include "ProjectReflect/Projectile/RProjectile.h"
#include "ProjectReflect/Utility/CollisionProfileNames.h"
#include "ProjectReflect/Utility/RSplineActor.h"

URProjectileTrajectoryComponent::URProjectileTrajectoryComponent()
{
}

void URProjectileTrajectoryComponent::SpawnTrajectorySpline()
{
	if(TrajectorySplineInstance == nullptr)
	{
		TrajectorySplineInstance = GetWorld()->SpawnActor<ARSplineActor>(TrajectorySplineBP,FVector::ZeroVector,FRotator::ZeroRotator,FActorSpawnParameters{});
	}

	if(TrajectoryReflectionSplineInstance == nullptr)
	{
		TrajectoryReflectionSplineInstance = GetWorld()->SpawnActor<ARSplineActor>(TrajectorySplineBP,FVector::ZeroVector,FRotator::ZeroRotator,FActorSpawnParameters{});
	}
	
	if(TrajectorySplineInstance)
	{
		TrajectorySplineInstance->SetActorScale3D(FVector{0.25,0.25,0.25});
		TrajectorySplineInstance->SetActorHiddenInGame(true);
		// TrajectorySplineActor->ClearNodes();
		// TrajectorySplineActor->SplineMeshMap = TrajectorySplineMap;
		// TrajectorySplineActor->UpdateSpline();
		// TrajectorySplineActor->SetReplicates(false);
	}
	if(TrajectoryReflectionSplineInstance)
	{
		TrajectoryReflectionSplineInstance->SetActorScale3D(FVector{0.25,0.25,0.25});
		TrajectoryReflectionSplineInstance->SetActorHiddenInGame(true);
	}
}

void URProjectileTrajectoryComponent::DrawTrajectorySplineFromWeapon(TArray<FVector> Path) const
{
	if(TrajectorySplineInstance)
	{
		TrajectorySplineInstance->ClearNodes();
			
		for(int i = 0; i < Path.Num(); i++)
		{
			TrajectorySplineInstance->AddNode(Path[i]);
		}
		TrajectorySplineInstance->UpdateSpline();
		TrajectorySplineInstance->SetActorHiddenInGame(false);
	}
}

void URProjectileTrajectoryComponent::DrawTrajectorySplineFromReflection(TArray<FVector> Path) const
{
	if(TrajectoryReflectionSplineInstance)
	{
		TrajectoryReflectionSplineInstance->ClearNodes();
			
		for(int i = 0; i < Path.Num(); i++)
		{
			TrajectoryReflectionSplineInstance->AddNode(Path[i]);
		}
		TrajectoryReflectionSplineInstance->UpdateSpline();
		TrajectoryReflectionSplineInstance->SetActorHiddenInGame(false);
	}
}

void URProjectileTrajectoryComponent::DrawTrajectory(FVector Origin, FVector ShootDir, ARProjectile* ProjectileBP, TArray<TObjectPtr<AActor>> ActorsToIgnore, const FVector& MuzzleLocation, const FRotator& MuzzleRotation)
{
	if(ProjectileBP && TrajectorySplineInstance)
	{
		FPredictProjectilePathResult ProjectileResult;

		auto MovementComponent = ProjectileBP->GetProjectileMovementComponent();
		auto GravityZ = FMath::Min(MovementComponent->GetGravityZ(), -0.001f);//Gravity is negative -980
		auto LaunchVelocity = ShootDir * MovementComponent->InitialSpeed;
		auto Radius = ProjectileBP->GetRadius();

		auto ProjectileParams = GetTrajectoryParams(Origin, LaunchVelocity, Radius, ActorsToIgnore, GravityZ, 0.7f);
		UGameplayStatics::PredictProjectilePath(GetWorld(), ProjectileParams, ProjectileResult);

		if(ProjectileResult.PathData.Num() > 0)
		{
			auto Path = TArray<FVector>();
			Path.Add(MuzzleLocation);
			Path.Add(ProjectileResult.PathData[ProjectileResult.PathData.Num() - 1].Location);
			DrawTrajectorySplineFromWeapon(Path);
		}
		
		if(ProjectileResult.HitResult.GetActor())
		{
			auto ReflectionVector = FMath::GetReflectionVector(LaunchVelocity, ProjectileResult.HitResult.Normal);
			auto ReflectParams = GetTrajectoryParams(ProjectileResult.HitResult.Location, ReflectionVector, Radius, ActorsToIgnore, GravityZ, 0.5f);

			FPredictProjectilePathResult ReflectResult;
			ReflectParams.ActorsToIgnore.Add(ProjectileResult.HitResult.GetActor());
			UGameplayStatics::PredictProjectilePath(GetWorld(), ReflectParams, ReflectResult);

			auto ReflectPath = TArray<FVector>();
			for (int i = 0; i < ReflectResult.PathData.Num(); ++i)
			{
				ReflectPath.Add(ReflectResult.PathData[i].Location);
			}
			DrawTrajectorySplineFromReflection(ReflectPath);
		}
		else
		{
			DisableSplineFromReflection();
		}
	}
}

FPredictProjectilePathParams URProjectileTrajectoryComponent::GetTrajectoryParams(FVector StartLocation, FVector Velocity, float Radius, TArray<TObjectPtr<AActor>> ActorsToIgnore, float Gravity, float SimTime)
{
	FPredictProjectilePathParams ProjectileParams;
	ProjectileParams.StartLocation = StartLocation;
	ProjectileParams.LaunchVelocity = Velocity;
	ProjectileParams.ProjectileRadius = Radius;
	ProjectileParams.bTraceWithCollision = true;
	ProjectileParams.TraceChannel = COLLISION_PROJECTILE;
	ProjectileParams.MaxSimTime = SimTime;
	ProjectileParams.ActorsToIgnore = ActorsToIgnore;
	ProjectileParams.OverrideGravityZ = Gravity;
	// ProjectileParams.DrawDebugType = EDrawDebugTrace::ForOneFrame;
	
	// ProjectileParams.ObjectTypes = ObjectTypesToHit;
	// ProjectileParams.bTraceWithChannel = true;
	// ProjectileParams.DrawDebugType = EDrawDebugTrace::ForOneFrame;
	// TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesToHit;
	// ObjectTypesToHit.Add(ObjectTypeQuery1);//World_Static
	// ObjectTypesToHit.Add(ObjectTypeQuery3);//Pawn
	// ObjectTypesToHit.Add(ObjectTypeQuery6);//Destructable
	// ObjectTypesToHit.Add(ObjectTypeQuery7);//Obstacles

	return ProjectileParams;
}

void URProjectileTrajectoryComponent::DisableSplineFromWeapon() const
{
	if(TrajectorySplineInstance)
	{
		TrajectorySplineInstance->SetActorHiddenInGame(true);
	}
}
void URProjectileTrajectoryComponent::DisableSplineFromReflection() const
{
	if(TrajectoryReflectionSplineInstance)
	{
		TrajectoryReflectionSplineInstance->SetActorHiddenInGame(true);
	}
}

void URProjectileTrajectoryComponent::ClearTrajectory()
{
	if(TrajectorySplineInstance)
	{
		TrajectorySplineInstance->ClearNodes();
		TrajectorySplineInstance->UpdateSpline();
		TrajectorySplineInstance->SetActorHiddenInGame(true);
		TrajectorySplineInstance->Destroy();
		TrajectorySplineInstance = nullptr;
	}

	if(TrajectoryReflectionSplineInstance)
	{
		TrajectoryReflectionSplineInstance->ClearNodes();
		TrajectoryReflectionSplineInstance->UpdateSpline();
		TrajectoryReflectionSplineInstance->SetActorHiddenInGame(true);
		TrajectoryReflectionSplineInstance->Destroy();
		TrajectoryReflectionSplineInstance = nullptr;
	}
}

