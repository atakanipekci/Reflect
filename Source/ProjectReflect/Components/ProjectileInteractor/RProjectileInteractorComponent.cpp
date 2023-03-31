// Fill out your copyright notice in the Description page of Project Settings.


#include "RProjectileInteractorComponent.h"
#include "ProjectReflect/Components/ProjectileInteractor/RProjectileBehaviorModifier.h"
#include "ProjectReflect/Projectile/RProjectile.h"


URProjectileInteractorComponent::URProjectileInteractorComponent()
{
}

void URProjectileInteractorComponent::BeginPlay()
{
	Super::BeginPlay();

	BehaviorModifiers.Empty();
	if(const auto Owner = GetOwner())
	{
		auto AllComponents = Owner->GetComponents();
		for (const auto Component : AllComponents)
		{
			if(auto ModifierComponent = Cast<URProjectileBehaviorModifier>(Component))
			{
				UE_LOG(LogStats, Log, TEXT("ProjectileInteractor Constructor addCOmponent -> %s"), *ModifierComponent->GetName());
				BehaviorModifiers.Add(ModifierComponent);
			}
		} 
	}
}

void URProjectileInteractorComponent::OnProjectileHit(ARProjectile* Projectile, const FHitResult& Hit)
{
	UE_LOG(LogStats, Log, TEXT("ProjectileInteractor OnHit -> %s"), *Projectile->GetName());
	OnProjectileHitDelegate.Broadcast(Projectile, Hit);
	for (const auto Modifier : BehaviorModifiers)
	{
		if(Modifier)
		{
			Modifier->ApplyBehavior(Projectile, Hit);
		}
	}

	if(!bEnableBounce && Projectile)
	{
		Projectile->DestroyProjectile();
	}
}

FVector URProjectileInteractorComponent::GetBounceDir(FVector Velocity, const FHitResult& Hit)
{
	if(BehaviorModifiers.Num() <= 0)
	{
		return FMath::GetReflectionVector(Velocity, Hit.Normal);
	}
	
	auto VecToModify = Velocity;
	for (const auto Modifier : BehaviorModifiers)
	{
		VecToModify = Modifier->GetBounceDir(VecToModify, Hit);
	}

	return VecToModify;
}

