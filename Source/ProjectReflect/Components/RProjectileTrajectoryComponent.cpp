// Fill out your copyright notice in the Description page of Project Settings.


#include "RProjectileTrajectoryComponent.h"

#include "Kismet/GameplayStatics.h"
#include "ProjectileInteractor/RProjectileInteractorComponent.h"
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
	}
	if(TrajectoryReflectionSplineInstance)
	{
		TrajectoryReflectionSplineInstance->SetActorScale3D(FVector{0.25,0.25,0.25});
		TrajectoryReflectionSplineInstance->SetActorHiddenInGame(true);
	}
}

void URProjectileTrajectoryComponent::DrawTrajectorySplineFromWeapon(TArray<FVector> Path) const
{
	DrawTrajectorySplineFromPath(TrajectorySplineInstance, Path);
}

void URProjectileTrajectoryComponent::DrawTrajectorySplineFromReflection(TArray<FVector> Path) const
{
	DrawTrajectorySplineFromPath(TrajectoryReflectionSplineInstance, Path);
}

void URProjectileTrajectoryComponent::DrawTrajectorySplineFromPath(ARSplineActor* Spline, TArray<FVector> Path) const
{
	if(Spline)
	{
		Spline->ClearNodes();
			
		for(int i = 0; i < Path.Num(); i++)
		{
			Spline->AddNode(Path[i]);
		}
		Spline->UpdateSpline();
		Spline->SetActorHiddenInGame(false);
	}
}

void URProjectileTrajectoryComponent::DrawTrajectory(FVector Origin, FVector ShootDir, ARProjectile* ProjectileBP, TArray<TObjectPtr<AActor>> ActorsToIgnore, const FVector& MuzzleLocation)
{
	if(ProjectileBP && IsTrajectoryActive())
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
		
		if(auto HitActor = ProjectileResult.HitResult.GetActor())
		{
			if(auto ProjectileInteractionComp = GetInteractorComponentFromActor(HitActor))
			{
				auto BounceDir = ProjectileInteractionComp->GetBounceDir(LaunchVelocity, ProjectileResult.HitResult);
				auto ReflectParams = GetTrajectoryParams(ProjectileResult.HitResult.Location, BounceDir, Radius, ActorsToIgnore, GravityZ, 0.5f);

				FPredictProjectilePathResult ReflectResult;
				ReflectParams.ActorsToIgnore.Add(ProjectileResult.HitResult.GetActor());
				UGameplayStatics::PredictProjectilePath(GetWorld(), ReflectParams, ReflectResult);

				auto ReflectPath = TArray<FVector>();
				for (int i = 0; i < ReflectResult.PathData.Num(); ++i)
				{
					ReflectPath.Add(ReflectResult.PathData[i].Location);
				}
				DrawTrajectorySplineFromReflection(ReflectPath);
				return;
			}
		}

		DisableSplineFromReflection();
	}
}

URProjectileInteractorComponent* URProjectileTrajectoryComponent::GetInteractorComponentFromActor(const AActor* OtherActor) const
{
	if(OtherActor)
	{
		if(const auto InteractorComponent = Cast<URProjectileInteractorComponent>(OtherActor->GetComponentByClass(URProjectileInteractorComponent::StaticClass())))
		{
			return InteractorComponent;
		}
	}

	return nullptr;
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

bool URProjectileTrajectoryComponent::IsTrajectoryActive() const
{
	return TrajectorySplineInstance != nullptr && TrajectoryReflectionSplineInstance != nullptr;
}

void URProjectileTrajectoryComponent::DestroyTrajectory()
{
	if(TrajectorySplineInstance)
	{
		TrajectorySplineInstance->Destroy();
		TrajectorySplineInstance = nullptr;
	}

	if(TrajectoryReflectionSplineInstance)
	{
		TrajectoryReflectionSplineInstance->Destroy();
		TrajectoryReflectionSplineInstance = nullptr;
	}
}

void URProjectileTrajectoryComponent::ClearTrajectory() const
{
	if(TrajectorySplineInstance)
	{
		TrajectorySplineInstance->ClearNodes();
		TrajectorySplineInstance->UpdateSpline();
		TrajectorySplineInstance->SetActorHiddenInGame(true);
	}

	if(TrajectoryReflectionSplineInstance)
	{
		TrajectoryReflectionSplineInstance->ClearNodes();
		TrajectoryReflectionSplineInstance->UpdateSpline();
		TrajectoryReflectionSplineInstance->SetActorHiddenInGame(true);
	}
}

