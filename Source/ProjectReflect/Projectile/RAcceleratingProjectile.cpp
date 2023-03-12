// Fill out your copyright notice in the Description page of Project Settings.


#include "RAcceleratingProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

ARAcceleratingProjectile::ARAcceleratingProjectile()
{
	SpeedBoostOnBounce = 500;
}

void ARAcceleratingProjectile::OnBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity)
{
	Super::OnBounce(ImpactResult, ImpactVelocity);
	auto VelocityToAdd = ProjectileMovement->Velocity;
	VelocityToAdd.Normalize();
	VelocityToAdd *= SpeedBoostOnBounce;
	const auto NewVelocity = (ProjectileMovement->Velocity + VelocityToAdd);
	
	UE_LOG(LogStats, Log, TEXT("Accelerating Projectile OnBounce OldVelocity: %f, new Velocity: %f"), ProjectileMovement->Velocity.Length(), FMath::Min(NewVelocity.Length(), ProjectileMovement->MaxSpeed));
	ProjectileMovement->Velocity = NewVelocity;
}
