// Fill out your copyright notice in the Description page of Project Settings.


#include "RProjectileBehaviorModifier.h"

void URProjectileBehaviorModifier::ApplyBehavior(ARProjectile* Projectile, const FHitResult& Hit)
{
	
}

FVector URProjectileBehaviorModifier::GetBounceDir(FVector Velocity, const FHitResult& Hit)
{
	return Velocity;
}
