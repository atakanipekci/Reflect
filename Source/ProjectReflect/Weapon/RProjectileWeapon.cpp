// Fill out your copyright notice in the Description page of Project Settings.


#include "RProjectileWeapon.h"

#include "ProjectReflect/RPlayerCharacter.h"
#include "ProjectReflect/RProjectile.h"

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
	
			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
			// Spawn the projectile at the muzzle
			AActor* Spawned = GetWorld()->SpawnActor<ARProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			if(Spawned)
			{
				
			}
		}
	}
}
