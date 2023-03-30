// Fill out your copyright notice in the Description page of Project Settings.


#include "RProjectileSpeedModifier.h"

#include "ProjectReflect/Projectile/RProjectile.h"

void URProjectileSpeedModifier::ApplyBehavior(ARProjectile* Projectile, const FHitResult& Hit)
{
	Super::ApplyBehavior(Projectile, Hit);

	if(Projectile == nullptr)
	{
		return;
	}

	if(UProjectileMovementComponent* ProjectileMovement = Projectile->GetProjectileMovementComponent())
	{
		ProjectileMovement->Velocity = ProjectileMovement->Velocity * SpeedMultiplier;
	}
}
