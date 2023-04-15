// Fill out your copyright notice in the Description page of Project Settings.

#include "RProjectileWeapon.h"

#include "Components/DecalComponent.h"
#include "Engine/DecalActor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "ProjectReflect/Components/RProjectileTrajectoryComponent.h"
#include "ProjectReflect/Projectile/RProjectile.h"

ARProjectileWeapon::ARProjectileWeapon()
{
	TrajectoryComponent = CreateDefaultSubobject<URProjectileTrajectoryComponent>(TEXT("Trajectory Component"));
}

void ARProjectileWeapon::Shoot(FVector Location, FRotator Rotation)
{
	if(IsShootCooldownActive())return;
	
	Super::Shoot(Location, Rotation);
	SpawnProjectile(Location, Rotation);
}

void ARProjectileWeapon::SpawnProjectile(FVector Location, FRotator Rotation)
{
	if (ProjectileClass)
	{
		if (GetWorld() && ProjectileClass)
		{
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			if(const auto SpawnedProjectile = GetWorld()->SpawnActor<ARProjectile>(ProjectileClass, Location, Rotation, ActorSpawnParams))
			{
				if(LastFiredProjectile)
				{
					LastFiredProjectile->DestroyProjectile();
				}
				
				SpawnedProjectile->OnProjectileHit.AddDynamic(this, &ARProjectileWeapon::OnProjectileHit);
				SpawnedProjectile->SetLifeSpan(1.f);
				LastFiredProjectile = SpawnedProjectile;
			}
		}
	}
}

void ARProjectileWeapon::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ARProjectileWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ARProjectileWeapon::DrawTrajectory(FVector SpawnPos, FVector Dir, TArray<TObjectPtr<AActor>> ActorsToIgnore) const
{
	if(TrajectoryComponent == nullptr || SkeletalMesh == nullptr || ProjectileClass == nullptr) return;
	
	const auto MuzzleLocation = SkeletalMesh->GetSocketLocation(MuzzleSocket);
	TrajectoryComponent->DrawTrajectory(SpawnPos, Dir, Cast<ARProjectile>(ProjectileClass.GetDefaultObject()), ActorsToIgnore, MuzzleLocation);
}

void ARProjectileWeapon::OnProjectileHit(AActor* OtherActor, const FHitResult& Hit)
{
	if(OtherActor != nullptr)
	{
		UE_LOG(LogStats, Log, TEXT("OnProjectileHit %s"), *OtherActor->GetName());

		CreateDecal(OtherActor, Hit);
	}
}

void ARProjectileWeapon::CreateDecal(AActor* Actor, const FHitResult& Hit)
{
	const auto Decal = GetWorld()->SpawnActor<ADecalActor>(Hit.Location, UKismetMathLibrary::MakeRotFromZ(Hit.Normal));
	if (Decal)
	{
		Decal->SetDecalMaterial(DecalMaterial);
		Decal->SetLifeSpan(5.0f);
		Decal->GetDecal()->DecalSize = FVector(64.0f, 64.0f, 64.0f);
	}
}
