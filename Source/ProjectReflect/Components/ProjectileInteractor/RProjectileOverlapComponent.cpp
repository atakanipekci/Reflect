// Fill out your copyright notice in the Description page of Project Settings.


#include "RProjectileOverlapComponent.h"

#include "RProjectileBehaviorModifier.h"
#include "ProjectReflect/Projectile/RProjectile.h"

URProjectileOverlapComponent::URProjectileOverlapComponent()
{
	if(GetOwner())
	{
		GetOwner()->OnActorBeginOverlap.AddDynamic(this, &URProjectileOverlapComponent::OnProjectileOverlap);
	}
}

void URProjectileOverlapComponent::OnProjectileOverlap(AActor* OverlappedActor, AActor* OtherActor )
{
	ARProjectile* Projectile = Cast<ARProjectile>(OtherActor);
	if(Projectile == nullptr)
	{
		return;
	}

	FHitResult HitResult;
	for (const auto Modifier : BehaviorModifiers)
	{
		if(Modifier)
		{
			Modifier->ApplyBehavior(Projectile, HitResult);
		}
	}
}
