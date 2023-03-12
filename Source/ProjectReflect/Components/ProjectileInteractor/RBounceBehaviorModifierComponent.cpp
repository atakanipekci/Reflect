// Fill out your copyright notice in the Description page of Project Settings.


#include "RBounceBehaviorModifierComponent.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "ProjectReflect/Projectile/RProjectile.h"

URBounceBehaviorModifierComponent::URBounceBehaviorModifierComponent()
{

}

void URBounceBehaviorModifierComponent::ApplyBehavior(ARProjectile* Projectile, const FHitResult& Hit)
{
	URProjectileBehaviorModifier::ApplyBehavior(Projectile, Hit);
	UE_LOG(LogStats, Log, TEXT("BounceBehaviorModifier ApplyBehavior"));
	if(const auto MovementComp = Projectile->GetProjectileMovementComponent())
	{
		const auto Lenght = MovementComp->Velocity.Length();
		MovementComp->Velocity = Hit.Normal*Lenght;
	}
}

