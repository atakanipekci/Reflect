// Fill out your copyright notice in the Description page of Project Settings.


#include "RProjectileWeapon.h"

#include "ProjectReflect/Character/RPlayerCharacter.h"
#include "ProjectReflect/Projectile/RProjectile.h"

void ARProjectileWeapon::Fire()
{
	SpawnProjectile();
	if(AttachedCharacter)
	{
		AttachedCharacter->PlayCharacterFireAnimation();
	}
}

void ARProjectileWeapon::SpawnProjectile() const
{
	if (ProjectileClass)
	{
		if (GetWorld() && AttachedCharacter && ProjectileClass)
		{
			ARPlayerCharacter* PlayerOwner = Cast<ARPlayerCharacter>(AttachedCharacter);
			const auto PlayerController = Cast<APlayerController>(PlayerOwner->GetController());
			const auto SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
			const auto SpawnLocation = PlayerController->PlayerCameraManager->GetCameraLocation() + SpawnRotation.RotateVector(FVector(200, 0, 0));
	
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			if(auto SpawnedProjectile = GetWorld()->SpawnActor<ARProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams))
			{
				SpawnedProjectile->OnProjectileHit.AddDynamic(this, &ARProjectileWeapon::OnProjectileHit);
			}
		}
	}
}


void ARProjectileWeapon::OnProjectileHit(AActor* OtherActor, const FHitResult& Hit)
{
	if(OtherActor != nullptr)
	{
		UE_LOG(LogStats, Log, TEXT("OnProjectileHit %s"), *OtherActor->GetName());
	}
}
