// Fill out your copyright notice in the Description page of Project Settings.


#include "RProjectileTrajectoryComponent.h"

#include "Kismet/GameplayStatics.h"
#include "ProjectReflect/Projectile/RProjectile.h"
#include "ProjectReflect/Utility/CollisionProfileNames.h"
#include "ProjectReflect/Utility/RSplineActor.h"

// Sets default values for this component's properties
URProjectileTrajectoryComponent::URProjectileTrajectoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URProjectileTrajectoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// SpawnTrajectorySpline();
}


// Called every frame
void URProjectileTrajectoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
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
		// TrajectorySplineActor->ClearNodes();
		// TrajectorySplineActor->SplineMeshMap = TrajectorySplineMap;
		// TrajectorySplineActor->UpdateSpline();
		// TrajectorySplineActor->SetReplicates(false);
	}
	if(TrajectoryReflectionSplineInstance)
	{
		TrajectoryReflectionSplineInstance->SetActorScale3D(FVector{0.25,0.25,0.25});
	}
}

void URProjectileTrajectoryComponent::DrawSpline(TArray<FVector> Path)
{
	if(TrajectorySplineInstance)
	{
		//ProjectileParams.LaunchVelocity = ProjectileConfig.ProjectileInitialSpeed;
		TrajectorySplineInstance->SetActorHiddenInGame(true);
		TrajectorySplineInstance->ClearNodes();
			
		for(int i = 0; i < Path.Num(); i++)
		{
			TrajectorySplineInstance->AddNode(Path[i]);
		}
		TrajectorySplineInstance->UpdateSpline();
		TrajectorySplineInstance->SetActorHiddenInGame(false);
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
		
		auto ProjectileParams = GetMainTrajectoryParams(Origin, LaunchVelocity, Radius, ActorsToIgnore, GravityZ);
		UGameplayStatics::PredictProjectilePath(GetWorld(), ProjectileParams, ProjectileResult);

		if(auto ActorHit = ProjectileResult.HitResult.GetActor())
		{
			auto Path = TArray<FVector>();
			Path.Add(MuzzleLocation);
			Path.Add(ProjectileResult.HitResult.Location);
			DrawSpline(Path);

			auto ReflectionVector = FMath::GetReflectionVector(LaunchVelocity, ProjectileResult.HitResult.Normal);
				
			auto ReflectParams = GetMainTrajectoryParams(ProjectileResult.HitResult.Location, ReflectionVector, Radius, ActorsToIgnore, GravityZ);

			FPredictProjectilePathResult ReflectResult;
			ReflectParams.ActorsToIgnore.Add(ProjectileResult.HitResult.GetActor());
			UGameplayStatics::PredictProjectilePath(GetWorld(), ReflectParams, ReflectResult);

			if(ReflectResult.HitResult.GetActor())
			{
				UE_LOG(LogTemp, Warning, TEXT("Reflection HitActor %s "), *ReflectResult.HitResult.GetActor()->GetName());
			}
			// DrawSpline(ReflectResult);
			if(TrajectoryReflectionSplineInstance)
			{
				//ProjectileParams.LaunchVelocity = ProjectileConfig.ProjectileInitialSpeed;
				TrajectoryReflectionSplineInstance->SetActorHiddenInGame(true);
				TrajectoryReflectionSplineInstance->ClearNodes();
			
				for(int i = 0; i < ReflectResult.PathData.Num(); i++)
				{
					TrajectoryReflectionSplineInstance->AddNode(ReflectResult.PathData[i].Location);
				}
				TrajectoryReflectionSplineInstance->UpdateSpline();
				TrajectoryReflectionSplineInstance->SetActorHiddenInGame(false);
			}
		}
	}
}

FPredictProjectilePathParams URProjectileTrajectoryComponent::GetMainTrajectoryParams(FVector StartLocation, FVector Velocity, float Radius, TArray<TObjectPtr<AActor>> ActorsToIgnore, float Gravity)
{
	FPredictProjectilePathParams ProjectileParams;
	ProjectileParams.StartLocation = StartLocation;
	ProjectileParams.LaunchVelocity = Velocity;
	ProjectileParams.ProjectileRadius = Radius;
	ProjectileParams.bTraceWithCollision = true;
	ProjectileParams.TraceChannel = COLLISION_PROJECTILE;
	ProjectileParams.MaxSimTime = 10;
	ProjectileParams.ActorsToIgnore = ActorsToIgnore;
	ProjectileParams.OverrideGravityZ = Gravity;
	
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

FPredictProjectilePathParams URProjectileTrajectoryComponent::GetMuzzleTrajectoryParams(FVector EndLocation, FVector MuzzleLocation, FRotator MuzzleRotation, float Radius, TArray<TObjectPtr<AActor>> ActorsToIgnore, float Gravity)
{
	FPredictProjectilePathParams ProjectileParamsFromMuzzle;
	ProjectileParamsFromMuzzle.ProjectileRadius = Radius;
	ProjectileParamsFromMuzzle.StartLocation = MuzzleLocation;
	ProjectileParamsFromMuzzle.DrawDebugType = EDrawDebugTrace::None;
	ProjectileParamsFromMuzzle.MaxSimTime = 10;
	ProjectileParamsFromMuzzle.bTraceWithCollision = true;
	ProjectileParamsFromMuzzle.TraceChannel = COLLISION_PROJECTILE;
	ProjectileParamsFromMuzzle.ActorsToIgnore = ActorsToIgnore;
	ProjectileParamsFromMuzzle.OverrideGravityZ = Gravity;
			
	// UE_LOG(LogTemp, Warning, TEXT("HITTED ACTOR %s "), *ActorHit->GetName());
	// auto Velocity = RTrajectoryHelper::GetVelocityPrediction(MuzzleLocation, EndLocation, MuzzleRotation.Pitch, ProjectileParamsFromMuzzle.OverrideGravityZ);
	// UE_LOG(LogTemp, Warning, TEXT("Muzzle Angle %f, Velocity %s"), MuzzleRotation.Pitch, *Velocity.ToString());
	// auto Velocity = (EndLocation - MuzzleLocation);
	// Velocity.Normalize();
	// Velocity *= 1000;
			
			
	FPredictProjectilePathResult ProjectileResultFromMuzzle;
	// FVector Velocity;
	// UGameplayStatics::SuggestProjectileVelocity_CustomArc(GetWorld(), Velocity, MuzzleLocation, EndLocation, Gravity, 0.75f);
	// ProjectileParamsFromMuzzle.LaunchVelocity = Velocity;
	// UE_LOG(LogTemp, Warning, TEXT("GetMuzzleTrajectoryParams->Speed %s "), *Velocity.ToString());

	auto DirToTarget = (EndLocation - MuzzleLocation);
	DirToTarget.Normalize();
	DirToTarget *= 1000;
	ProjectileParamsFromMuzzle.LaunchVelocity = DirToTarget;
	
	return ProjectileParamsFromMuzzle;
}

void URProjectileTrajectoryComponent::ClearTrajectory()
{
	if(TrajectorySplineInstance == nullptr)
	{
		return;
	}
	TrajectorySplineInstance->ClearNodes();
	TrajectorySplineInstance->UpdateSpline();
	TrajectorySplineInstance->SetActorHiddenInGame(true);
	TrajectorySplineInstance->Destroy();
	TrajectorySplineInstance = nullptr;
}

