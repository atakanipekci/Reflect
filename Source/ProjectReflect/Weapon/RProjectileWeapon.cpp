// Fill out your copyright notice in the Description page of Project Settings.


#include "RProjectileWeapon.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "ProjectReflect/Character/RPlayerCharacter.h"
#include "ProjectReflect/Components/RProjectileTrajectoryComponent.h"
#include "ProjectReflect/Projectile/RProjectile.h"

ARProjectileWeapon::ARProjectileWeapon()
{
	TrajectoryComponent = CreateDefaultSubobject<URProjectileTrajectoryComponent>(TEXT("Trajectory Component"));
}

void ARProjectileWeapon::Fire()
{
	SpawnProjectile();
	if(AttachedCharacter)
	{
		AttachedCharacter->PlayCharacterFireAnimation();
	}
}

FRotator ARProjectileWeapon::GetProjectileSpawnRotation() const
{
	//TODO CHANGE Calculation
	return  PlayerController->PlayerCameraManager->GetCameraRotation();
}

FVector ARProjectileWeapon::GetProjectileSpawnLocation(const FRotator SpawnRotation) const
{
	//TODO CHANGE Calculation
	return PlayerController->PlayerCameraManager->GetCameraLocation() + SpawnRotation.RotateVector(FVector(200, 0, 0));
}

void ARProjectileWeapon::SpawnProjectile() const
{
	if (ProjectileClass)
	{
		if (GetWorld() && AttachedCharacter && ProjectileClass && PlayerController)
		{
			const auto SpawnRotation = GetProjectileSpawnRotation();
			const auto SpawnLocation = GetProjectileSpawnLocation(SpawnRotation);

			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			if(const auto SpawnedProjectile = GetWorld()->SpawnActor<ARProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams))
			{
				SpawnedProjectile->OnProjectileHit.AddDynamic(this, &ARProjectileWeapon::OnProjectileHit);
			}
		}
	}
}

void ARProjectileWeapon::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const FVector Origin = GetProjectileSpawnLocation(GetProjectileSpawnRotation());
	
	FVector CamLoc;
	FRotator CamRot;
	PlayerController->GetPlayerViewPoint(CamLoc, CamRot);

	const FVector ShootDir = CamRot.Vector();

	const auto ProjectileBP = Cast<ARProjectile>(ProjectileClass.GetDefaultObject());
	/** If there is no dynamic object on the map that can collide with the projectile, you can optimize this to
	 only update when player moves themselves or moves their aim*/

	TArray<TObjectPtr<AActor>> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	if(AttachedCharacter)
	{
		ActorsToIgnore.Add(AttachedCharacter);
	}

	const auto MuzzleLocation = SkeletalMesh->GetSocketLocation(MuzzleSocket);
	const auto MuzzleRotation = SkeletalMesh->GetSocketRotation(MuzzleSocket);

	TrajectoryComponent->DrawTrajectory(Origin, ShootDir, ProjectileBP, ActorsToIgnore, MuzzleLocation, MuzzleRotation);
	//ClearTrajectory();
}

void ARProjectileWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARProjectileWeapon::OnProjectileHit(AActor* OtherActor, const FHitResult& Hit)
{
	if(OtherActor != nullptr)
	{
		UE_LOG(LogStats, Log, TEXT("OnProjectileHit %s"), *OtherActor->GetName());
	}
}
