// Fill out your copyright notice in the Description page of Project Settings.


#include "RProjectileDestroyerComponent.h"

#include "ProjectReflect/Projectile/RProjectile.h"

void URProjectileDestroyerComponent::ApplyBehavior(ARProjectile* Projectile, const FHitResult& Hit)
{
	Super::ApplyBehavior(Projectile, Hit);

	if(Projectile)
	{
		Projectile->DestroyProjectile();
	}
}
